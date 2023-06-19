/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:55:58 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 13:43:29 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_herdoc(char *del, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(CYAN "herdoc >> " RESET);
		if (!line || !ft_strcmp(del, line))
			break ;
		expand(&line);
		if (line[0] == '$')
			line = ft_strdup("");
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

void	store_herdoc_fds(t_list *commands_lst)
{
	t_command	*commands;
	int			fds[2];
	t_list		*tmp_redir;
	t_red		*red;

	commands = (t_command *)commands_lst->content;
	tmp_redir = commands->redir_in_out;
	while (tmp_redir)
	{
		red = (t_red *)tmp_redir->content;
		if (!red->flag)
		{
			if (pipe(fds) == -1)
				print_cmd_error(commands->cmd, NULL, strerror(errno), 1);
			exec_herdoc(red->file_name, fds[1]);
			red->fd_herdoc = fds[0];
			close(fds[1]);
		}
		tmp_redir = tmp_redir->next;
	}
}

void	herdoc(t_list *command_lst)
{
	t_list	*tmp_command_lst;

	tmp_command_lst = NULL;
	tmp_command_lst = command_lst;
	while (tmp_command_lst)
	{
		store_herdoc_fds(tmp_command_lst);
		tmp_command_lst = tmp_command_lst->next;
	}
}
