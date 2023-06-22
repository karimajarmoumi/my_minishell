/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:18 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 18:02:41 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_builtins(t_list *commands)
{
	t_command	*tmp_command;
	int			infile;
	int			outfile;

	tmp_command = (t_command *)commands->content;
	infile = 0;
	outfile = 1;
	if (commands && !commands->next)
	{
		if (tmp_command->cmd && (!ft_strcmp(tmp_command->cmd, "unset")
				|| !ft_strcmp(tmp_command->cmd, "export")
				|| !ft_strcmp(tmp_command->cmd, "cd")
				|| !ft_strcmp(tmp_command->cmd, "exit")))
		{
			if (!ft_strcmp(tmp_command->cmd, "exit"))
				printf("exit\n");
			get_fds(tmp_command->redir_in_out, &infile, &outfile);
			g_data.status_code = execute_bultin(tmp_command, outfile);
			return (g_data.status_code);
		}
	}
	return (-1);
}

void	execute_child(t_list *lst_command, int last_fd, int *fds)
{
	int			pipe_out_fd;
	t_command	*command;

	pipe_out_fd = fds[1];
	command = (t_command *)lst_command->content;
	signals_for_child();
	get_fds(command->redir_in_out, &last_fd, &fds[1]);
	duplicate_fds(lst_command, last_fd, fds, pipe_out_fd);
	execute_command(command, get_my_path(command));
	exit(g_data.status_code);
}

int	execuet_pipe(t_list *lst_command, int *last_fd)
{
	int	pid;
	int	fds[2];

	if (pipe(fds) == -1)
		print_cmd_error(NULL, NULL, strerror(errno), 1);
	pid = fork();
	if (pid == -1)
	{
		print_cmd_error(NULL, NULL,
			" fork: Resource temporarily unavailable", 1);
		exit(g_data.status_code);
	}
	if (!pid)
		execute_child(lst_command, *last_fd, fds);
	else
	{
		if (*last_fd != 0)
			close(*last_fd);
		*last_fd = fds[0];
		close(fds[1]);
		return (pid);
	}
	return (0);
}

void	executer(t_list *commands)
{
	t_list		*tmp;
	int			pidd[MAX_PIPE];
	int			i;
	int			last_fd;

	tmp = commands;
	i = 0;
	last_fd = STDIN_FILENO;
	if (run_builtins(tmp) >= 0)
		return ;
	g_data.isChild = 1;
	while (tmp)
	{
		pidd[i] = execuet_pipe(tmp, &last_fd);
		i++;
		tmp = tmp->next;
	}
	closing_pipe(commands, pidd, i);
}
