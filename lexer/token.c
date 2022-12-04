/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:31:34 by nel-brig          #+#    #+#             */
/*   Updated: 2022/11/25 16:31:36 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../minishell.h"

char	*get_string_without_expand(t_lexer *lexer, char **s)
{
	if (lexer->c == '$')
	{
		*s = get_char_as_string('$');
		lexer_advance(lexer);
	}
	else if (lexer->c != '$')
		*s = get_str(lexer);
	return (*s);
}

int	is_whitespaces(char c)
{
	if (c == ' ' || c == '\t')
		return (0);
	return (1);
}

char	*get_env(char *str)
{
	int		i;
	char	*s;
	t_env	*tmp;	

	i = 0;
	s = NULL;
	if (str == NULL)
		return (NULL);
	tmp = var->envc;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->line, str, ft_strlen(str)) == 0
			&& tmp->line[ft_strlen(str)] == '=')
		{
			s = ft_strdup(tmp->line + ft_strlen(str) + 1);
			return (s);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_token	*init_token(int type, char *s)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->type = type;
	if (s != NULL)
		token->value = ft_strdup(s);
	else
		token->value = NULL;
	token->next = NULL;
	free(s);
	s = NULL;
	return (token);
}

void	add_token_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
