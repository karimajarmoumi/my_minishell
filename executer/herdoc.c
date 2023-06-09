/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:55:58 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/09 15:11:55 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
void	exec_herdoc(char *del, int fd)
{
	char	*line;
	while (1)
	{
		line = readline(CYAN "herdoc >> " RESET);
		if (!ft_strncmp(del, line, ft_strlen(line)))
			break ;
		// parsing_function_for expand
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

void store_herdoc_fds(t_list *commands_lst)
{
	t_command *commands;
	int pid;
	int fds[2];
	int status;

	commands=(t_command*)commands_lst->content;
	t_list *tmp_redir=commands->redir_in;

	t_red *red;
	int last_fd;
	while(tmp_redir)
	{
		red=(t_red*)tmp_redir->content;
		if(!red->flag)
		{
			if (pipe(fds) == -1)
				printf("erooor\n");
			exec_herdoc(red->file_name, fds[1]);
			red->flag=fds[0];
			close(fds[1]);

		}
		tmp_redir=tmp_redir->next;
	}
}

void herdoc(t_list *command_lst)
{
	int pid;
	int fds[2];
	int last_fd;
	t_list *tmp_command_lst=NULL;
	tmp_command_lst=command_lst;
	while(tmp_command_lst)
	{
		store_herdoc_fds(tmp_command_lst);
		tmp_command_lst=tmp_command_lst->next;
	}
}
