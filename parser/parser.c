/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:26:25 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 23:07:20 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "../minishell.h"

void	remove_s_d_qoute(char **buffer)
{
	char	*tmp;
	char	*to_free;

	if (buffer)
	{
		if ((*buffer)[0] == '"' || (*buffer)[0] == '\'')
		{
			to_free = *buffer;
			(*buffer)++;
			tmp = malloc(sizeof(char) * ft_strlen(*buffer));
			if (ft_strlen(*buffer) == 2)
				ft_strlcpy(tmp, *buffer, ft_strlen(*buffer) - 1);
			else
				ft_strlcpy(tmp, *buffer, ft_strlen(*buffer));
			*buffer = tmp;
			function_free((void **)&to_free, 1);
		}
	}
}

void	check_tild(t_token **token_cmd)
{
	char	*value;
	char	*to_free;

	if (*token_cmd)
	{
		if ((*token_cmd)->value[0] == '~')
		{
			if ((*token_cmd)->value[1] == '\0')
				(*token_cmd)->value = HOME;
			if ((*token_cmd)->value[1] == ' ' || (*token_cmd)->value[1] == '/')
			{
				to_free = (*token_cmd)->value;
				value = ft_strdup(&((*token_cmd))->value[1]);
				(*token_cmd)->value = ft_strjoin(HOME, value);
				function_free((void **)&value, 1);
				function_free((void **)&to_free, 1);
			}
		}
	}
}

t_list	*parser(char *line)
{
	int		flg_err;
	char	*symb;
	t_list	*lst;
	t_lexer	*lexer;
	t_token	*token;

	flg_err = 0;
	while(1);
	lexer = init_lexer(line);
	symb = ft_strdup("<>");
	token = get_all_tokens(lexer);
	function_free((void **)&lexer, 0);
	check_parsing_error(token, &flg_err);
	if (flg_err == 1)
	{
		function_free((void **)&symb, 1);
		function_free((void **)&token, 2);
		add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code), NULL);
		return (NULL);
	}
	lst = store_all_cmd(&token, symb);
	(function_free((void **)&symb, 1)) && (function_free((void **)&token, 2));
	if (herdoc(lst) == 2)
		return (free_commands(lst), NULL);
	return (lst);
}
