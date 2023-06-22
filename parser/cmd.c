/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:02:55 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/06/22 22:05:41 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "token.h"
#include "lexer.h"
#include "../minishell.h"

void	fill_args(t_command **new, char **cmd_args)
{
	if (cmd_args && *cmd_args)
	{
		(*new)->args = copy_of_tab(cmd_args);
		(*new)->cmd = ft_strdup((*new)->args[0]);
	}
	else
	{
		(*new)->args = NULL ;
		(*new)->cmd = NULL;
	}
}

void	fill_redir(t_command **new, char symb_file, char next_symb, int *i)
{
	if (symb_file == '>')
	{
		if (next_symb == '>')
			(*new)->redir_in_out->content = init_red(2, i);
		else if (symb_file == '>')
			(*new)->redir_in_out->content = init_red(3, i);
	}
	else if (symb_file == '<')
	{
		if (next_symb == '<')
		{
			(*new)->redir_in_out->content = init_red(0, i);
			g_data.count_herdoc++;
		}
		else if (symb_file == '<')
			((*new)->redir_in_out->content = init_red(1, i));
	}
}

void	insert_one_cmd_join_file_name(char *symb_file, char **file, int *i)
{
	char		*to_free;
	char		*c_string;

	while (symb_file[*i] && symb_file[*i] != ' ' && symb_file[*i] != '<'
		&& symb_file[*i] != '>')
	{
		to_free = (*file);
		c_string = char_to_string(symb_file[*i]);
		(*file) = ft_strjoin((*file), c_string);
		function_free((void **)&c_string, 1);
		function_free((void **)&to_free, 1);
		(*i)++;
	}
}

t_command	*insert_one_cmd(char **cmd_args, char *symb_file)
{
	int			i;
	char		*file;
	t_list		*lst_redir;
	t_command	*new;

	i = 0;
	new = malloc(sizeof(t_command));
	lst_redir = NULL;
	fill_args(&new, cmd_args);
	while (symb_file && symb_file[i])
	{
		new->redir_in_out = malloc(sizeof(t_list));
		if (new->redir_in_out)
		{
			fill_redir(&new, symb_file[i], symb_file[i + 1], &i);
			file = ft_strdup("");
			while (symb_file[i] && symb_file[i] == ' ')
				i++;
			insert_one_cmd_join_file_name(symb_file, &file, &i);
			((t_red *)new->redir_in_out->content)->file_name = file;
			ft_lstadd_back(&lst_redir, ft_lstnew(new->redir_in_out->content));
		}
	}
	new->redir_in_out = lst_redir;
	return (new);
}
