/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:22:57 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/04 16:20:27 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer/lexer.h"
#include "minishell.h"

void	exit_with_success(char **av)
{
	(void)av;
	exit(EXIT_SUCCESS);
}

void	exit_with_status(void)
{
	printf("exit8\n");
	exit(var->status);
}

void	parse_and_execute(t_token *token, t_parser *cmd_table)
{
	// print_tokens(token);
	cmd_table = parse_cmd(token);
	ft_execute(cmd_table);
	free_all_struct(token, cmd_table);
}

char	*get_line(void)
{
	char	*line;

	line = NULL;
	var->flag = 0;
	signal_main();
	line = readline("minishell$> ");
	if (line == 0x0)
		exit_with_status();
	return (line);
}

void	main_func(char *line, t_lexer *lexer, t_token *token, t_parser *cmd_table)
{
	if (check_quotes(line) == -1)
	{
		set_status_and_free(line, token, lexer, 0);
		return ;
	}
	lexer = init_lexer(line);
	token = get_token(lexer);
	if (syntax(token) == -1)
	{
		set_status_and_free(line, token, lexer, 1);
		return ;
	}
	if (token != NULL)
		parse_and_execute(token, cmd_table);
	free_lexer_and_line(lexer, line);
	// system("leaks minishell");
}
