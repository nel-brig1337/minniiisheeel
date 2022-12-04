/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:15:48 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/04 13:59:44 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "../minishell.h"

t_files	*init_file(t_token *tab, int type)
{
	t_files	*file;

	file = malloc(sizeof(t_files));
	if (!file)
		return (NULL);
	file->type = type;
	file->filename = ft_strdup(tab->value);
	file->next = NULL;
	return (file);
}

void	add_file_back(t_files **files, t_files *new)
{
	t_files	*tmp;

	if (!*files)
	{
		*files = new;
		return ;
	}
	tmp = *files;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_files	*fill_files(t_token *tab)
{
	t_token	*tmp;
	int		type;
	t_files	*files;

	tmp = tab;
	files = NULL;
	while (tmp != NULL)
	{
		type = tmp->type;
		if (type == R_RED || type == L_RED || type == APP || type == DEL)
		{
			tmp = tmp->next;
			if (tmp->type == AMB)
				type = AMB;
			add_file_back(&files, init_file(tmp, type));
		}
		tmp = tmp->next;
	}
	return (files);
}
