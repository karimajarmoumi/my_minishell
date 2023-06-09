/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:36:11 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/05 10:36:13 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	get_outfile_fd(int *fd, t_list *file_list)
{
	t_list	*tmp;
	t_red	*tmp_redir;

	tmp = file_list;
	while (tmp)
	{
		tmp_redir = (t_red *)tmp->content;
		if (tmp_redir->flag)
			*fd = open(tmp_redir->file_name, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else
			*fd = open(tmp_redir->file_name, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (*fd == -1)
			return (print_cmd_error(tmp_redir->file_name, NULL, strerror(errno),
					1));
		if (tmp->next && *(fd) != STDOUT_FILENO)
			close(*fd);
		tmp = tmp->next;
	}
	return (0);
}

int	get_inputfile_fd(int *last_fd, t_list *redir_in)
{
	t_list	*tmp_redir_in;
	t_red	*tmp;

	tmp_redir_in = redir_in;
	while (tmp_redir_in)
	{
		tmp = (t_red *)tmp_redir_in->content;
		if (tmp->flag == 1)
			*(last_fd) = open(tmp->file_name, O_RDONLY, 0644);
		if (*(last_fd) == -1)
			return (g_data.status_code = print_cmd_error(tmp->file_name, NULL,
					strerror(errno), 1));
		if ((tmp->flag) != 1)
			*last_fd = tmp->flag;
		if (tmp_redir_in->next && *last_fd)
			close(*last_fd);
		tmp_redir_in = tmp_redir_in->next;
	}
	return (0);
}

void	duplicate_fds(t_list *tmp, int last_fd, int *fds)
{
	t_command	*tmp_command;

	tmp_command = (t_command *)tmp->content;
	if (last_fd != STDIN_FILENO)
	{
		dup2(last_fd, STDIN_FILENO);
		close(last_fd);
	}
	if (tmp->next || tmp_command->redir_out)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
}
