/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:57:17 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/17 13:57:22 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_red(t_list *redir_list)
{
	t_list	*tmp_redir_list;
	t_list	*next;
	t_red	*tmp_red;

	tmp_redir_list = redir_list;
	while (tmp_redir_list)
	{
		tmp_red = (t_red *)tmp_redir_list->content;
		if (tmp_red)
			ft_free(tmp_red->file_name);
		next = tmp_redir_list->next;
		ft_free(tmp_redir_list);
		tmp_redir_list = next;
	}
}

void	free_commands(t_list *commands)
{
	t_list		*tmp_commands;
	t_command	*cmd;
	t_list		*next;

	tmp_commands = commands;
	while (tmp_commands)
	{
		cmd = (t_command *)tmp_commands->content;
		ft_free(cmd->cmd);
		free_double_ptr(cmd->args);
		free_red(cmd->redir_in_out);
		ft_free(cmd);
		next = tmp_commands->next;
		ft_free(tmp_commands);
		tmp_commands = next;
	}
}
