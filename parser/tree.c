/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:24:56 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/30 17:41:53 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "cmd.h"
#include "lexer.h"
#include "token.h"
#include "tree.h"

int	count_cmds(token_t *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->value[0] == '|')
			i++;
		token = token->next;
	}
	return (i);
}

t_list	*init_list(t_command *cmd)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->content = (t_command *)cmd;
	list->next = NULL;
	return (list);
}

// function check if cmd contain <
// int contain_redin(t_command *cmd)
// {
// 	int i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '<')
// 			return (1);
// 		i++;
// 	}
// 	return (1);
// }

// t_list init_list_redin()
// {

// }

//store redir_in || redir_out if existing
// void more_about_commmand(t_command **cmd)
// {
// 	int i;

// 	i = 0;
// 	while ((*cmd)->args[i])
// 	{
// 		if (contain_redout(cmd) > 0)
// 			(*cmd)->redir_in->
// 		i++;
// 	}
// }

// t_list *add_to_list(token_t **token)
// {
// 	t_list		*head;
// 	t_command	*cmd;

// 	head = NULL;
// 	cmd = get_one_command(token);
// 	while (cmd)
// 	{

// 		ft_lstadd_back(&head, init_list(cmd));

// 		cmd = get_one_command(token);
// 	}
// 	return (head);
// }

// int count_number_of_redin(t_command *cmd)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '<' && cmd[i] != '<')
// 			j++;
// 		i++;
// 	}
// 	return (j);
// }

// void store_redin(t_list **list)
// {
// 	if (list && *list)
// 	{
// 		(*list)->
// 	}
// }

// void add_node_to_list(token_t **token)
// {
// 	t_list		*list;
// 	t_command	*cmd;

// 	list = NULL;
// 	cmd = get_one_command(token);
// 	while (cmd)
// 	{
// 		if (count_number_of_redin(cmd) > 1)
// 		{
// 			store_redin()
// 		}
// 	}

// }