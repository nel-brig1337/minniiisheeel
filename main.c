/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:35:42 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/04 16:36:32 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "minishell.h"

t_global	*var;

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_lexer		*lexer;
	t_token		*token;
	t_parser	*cmd_table;

	if (ac != 1 || !envp)
		exit_with_success(av);
	init_variables(&token, &cmd_table, envp, &line);
	lexer = NULL;
	while (1)
	{
		line = get_line();    
		if (ft_strcmp(line, "\0") != 0)
			main_func(line, lexer, token, cmd_table);
		else
			free(line);
	}
}
