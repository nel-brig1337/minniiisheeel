/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 07:54:45 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/04 18:38:02 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	ft_dup2(int fd[2], int save, t_parser *prog)
{
	if (prog->next != NULL)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (save != -1)
	{
		dup2(save, 0);
		close(save);
	}
	if (var->fd_out != 1)
		dup2(var->fd_out, 1);
	if (var->fd_in != 0)
	{
		dup2(var->fd_in, 0);
		close(var->fd_in);
	}
}

char	*get_path_and_check(t_parser *prog)
{
	char	*path;

	path = NULL;
	if (access(prog->args[0], X_OK))
	{
		if (isdir(prog->args[0]))
			directory_error(prog->args[0]);
		else
		{
			path = find_path(create_paths(var->envc), prog->args[0]);
			cmd_error_check(prog->args[0], path);
		}
	}
	else
		path = ft_strdup(prog->args[0]);
	return (path);
}

void	ft_execeve(t_parser *prog)
{
	char	*path;

	path = NULL;
	if (prog->args[0][0] == '\0')
		not_found_error(prog->args[0]);
	if (prog->args[0][0] == '/')
		path = get_path_and_check(prog);
	else
		path = find_path(create_paths(var->envc), prog->args[0]);
	if (execve(path, prog->args, duplicate(var->envc)) == -1)
		not_found_error(prog->args[0]);
}

void	execute_child(t_parser *prog, int fd[2], int save, char *heredoc)
{
	signal_in();
	close(fd[0]);
	ft_dup2(fd, save, prog);
	if (prog->args == NULL)
		exit(var->status);
	if (builtin_check(prog->args[0]) == 1)
	{
		exec_builtin(prog, heredoc);
		exit(var->status);
	}
	else
		ft_execeve(prog);
}

void	waiting(int id, int fd[2], short flag)
{
	int	status;
	
	while (waitpid(id, &status, 0) != -1)
		;
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (!flag && WIFEXITED(status))
		var->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		var->status = WTERMSIG(status) + 128;
	close(fd[0]);
}

void	multicmds(t_parser *prog, char **heredoc)
{
	int			fd[2];
	int			id;
	int			save;
	int			i;
	t_parser	*tmp;
	short		flag;

	tmp = prog;
	flag = 0;
	init_vars(&save, &i);
	while (tmp != NULL)
	{
		if ((file_prep(tmp, heredoc[i]) == -1))
			flag = (!tmp->next);	
		else
		{
			if (pipe(fd) == -1)
				exit(var->status);
			id = fork();
			if (id == 0)
				execute_child(tmp, fd, save, heredoc[i]);
			handle_files(&save, fd);
		}
		tmp = tmp->next;
		reset_files(&i);
	}
	waiting(id, fd, flag);
}
