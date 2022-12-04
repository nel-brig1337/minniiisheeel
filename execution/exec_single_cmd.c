/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:07:00 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/04 14:15:35 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	cmd_error_check(char *arg, char *path)
{
	if (!path)
	{
		if (access(arg, F_OK) && last_with_back(arg))
			no_directory(arg);
		if (arg[0] == '.' || arg[0] == '/')
		{
			if (access(arg, X_OK))
				permission_error(arg);
		}
		else
			not_found_error(arg);
	}
}

void	single_cmd_wait(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		var->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		var->status = WTERMSIG(status) + 128;
}

void	ft_dup_in_single(void)
{
	dup2(var->fd_in, 0);
	dup2(var->fd_out, 1);
}

void	exec_single_cmd(t_parser *prog, char *heredoc)
{
	int		pid;
	char	*path;

	if (file_prep(prog, heredoc) == -1 || !prog->args)
		return ;
	signal_before();
	pid = fork();
	if (!pid)
	{
		signal_in();
		ft_dup_in_single();
		if(prog->args[0][0] == '\0')
			not_found_error(prog->args[0]);
		if (prog->args[0][0] == '/')
			path = get_path_and_check(prog);
		else
			path = find_path(create_paths(var->envc), prog->args[0]);
		if (execve(path, prog->args, duplicate(var->envc)) == -1)
			not_found_error(prog->args[0]);
	}
	cleanup_fd();
	single_cmd_wait(pid);
}
