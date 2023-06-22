/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_all_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:08:32 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 20:00:34 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"

void	store_all_cmd_free_part(t_list **lst,
	char **symb_file, t_token *cmd_arg)
{
	char	**tab;

	tab = token_cmd_to_args(cmd_arg);
	ft_lstadd_back(lst, ft_lstnew(insert_one_cmd(tab, *symb_file)));
	function_free((void **)tab, 3);
}

t_list	*store_all_cmd(t_token **tokens, char *symb)
{
	char		*symb_file;
	t_list		*lst;
	t_token		*cmd_arg;
	t_token		*tokens_cmd;
	t_token		*to_free;

	lst = NULL;
	if (*tokens && symb)
	{
		tokens_cmd = tokens_of_one_command(tokens);
		while (tokens_cmd)
		{
			cmd_arg = cmd_args_file(tokens_cmd, &symb_file);
			store_all_cmd_free_part(&lst, &symb_file, cmd_arg);
			function_free((void **)&symb_file, 1);
			free_same_type((void **)&cmd_arg, (void **)&tokens_cmd, 2);
			to_free = tokens_cmd;
			tokens_cmd = tokens_of_one_command(tokens);
			function_free((void **)&to_free, 2);
		}
	}
	return (lst);
}
