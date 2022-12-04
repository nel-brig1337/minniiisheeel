/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 07:54:57 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/04 16:38:54 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"



void	reset_files(int *i)
{
	var->fd_in = 0;
	var->fd_out = 1;
	*i += 1;
}

void	init_vars(int *save, int *i)
{
	*save = -1;
	*i = 0;
}

void	skip_to_another_cmd(t_parser *tmp, int *i)
{
	tmp = tmp->next;
	*i += 1;
}

void	handle_files(int *save, int fd[2])
{
	if (*save != -1)
		close(*save);
	*save = fd[0];
	close (fd[1]);
}
