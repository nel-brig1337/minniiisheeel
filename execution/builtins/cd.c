/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 04:15:29 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/04 19:25:01 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	change_pwd(t_env **env, char *pwd, char *type)
{
	t_env	*tmp;
	char	*new_line;
	char	*typ;
	int		i;

	tmp = *env;
	i = 0;
	new_line = NULL;
	typ = ft_strjoin_exec(type, "=");
	new_line = ft_strjoin_exec(typ, pwd);
	
	free(typ);
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, type, ft_strlen(type)))
		{
			free(tmp->line);
			tmp->line = new_line;
			break;
		}
		tmp = tmp->next;
	}
}

void	cd_error(char *dir)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(dir, 1);
	ft_putstr_fd(": ", 1);
	perror("");
	var->status = -101;
}

void	var_not_set(void)
{
	ft_putstr_fd("bash: cd: HOME not set\n", 2);
	var->status = 1;
}

void	reset_cd_status(int stat)
{
	if (stat == -101)
		var->status = 1;
	else
		var->status = 0;
}

void	ft_cd(t_parser	*prog)
{
	int		stat;
	char	*line;
	char	*cwd;

	line = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		chdir(prog->args[1]);
	else
	{
		
		change_pwd(&var->envc, cwd, "OLDPWD");
		if (prog->args[1])
		{
			stat = chdir(prog->args[1]);
			if (stat != 0)
				cd_error(prog->args[1]);
		}
		else
		{
			line = get_envc(var->envc, "HOME");
			if (!line)
				var_not_set();
			else
				chdir(line);
		}
		free(cwd);
		cwd = getcwd(NULL, 0);
		change_pwd(&var->envc, cwd, "PWD");
		reset_cd_status(var->status);
	}
	free(cwd);
	free(line);
}
