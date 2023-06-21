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

void	execute_command(t_command *tmp_command, char *path)
{
	char	**envs;
	int		status;

	status = 127;
	if (!is_bultin(tmp_command->cmd))
	{
		g_data.status_code = execute_bultin(tmp_command,1);
		return ;
	}
	else
	{
		envs = convert_tree_to_array();
		if (execve(path, tmp_command->args, envs) == -1)
			exit(status);
	}
}

void	closing_pipe(t_list *commands, int *pidd, int i)
{
	int	j;
	int	status;

	j = 0;
	if (commands)
	{
		while (j < i)
		{
			waitpid(pidd[j], &status, 0); 
			j++;
		}
		if (status == SIGINT)
			g_data.status_code = 130;
		else if (status == SIGQUIT)
		{
			g_data.status_code = 131;
			printf("Quit: 3\n");
		}
		else
			g_data.status_code = WEXITSTATUS(status);
		g_data.isChild=0;
	}
}

char	*get_my_path(t_command *tmp_command)
{
	char	*path;

	path = NULL;
	if (!(tmp_command->cmd))
		exit(0);
	if (is_bultin(tmp_command->cmd))
	{
		path = get_actual_path(tmp_command->cmd);
		if (!path)
			g_data.status_code = print_cmd_error(tmp_command->cmd, NULL,
				" command not found", 127);
	}
	return (path);
}

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

void	executer(t_list *commands)
{
	int			fds[2];
	t_list		*tmp;
	int			pidd[1000];
	int			i;
	t_command	*tmp_command;
	int			pid;
	int			last_fd;
	int			tmp_write_pipe;

	tmp = commands;
	i = 0;
	last_fd = STDIN_FILENO;
	if (run_builtins(tmp) >= 0)
		return ;
	g_data.isChild=1;
	while (tmp)
	{
		tmp_command = (t_command *)tmp->content;
		if (pipe(fds) == -1)
			print_cmd_error(tmp_command->cmd, tmp_command->args[1],
				strerror(errno), 1);
		pid = fork();
		if (pid == -1)
		{
			print_cmd_error(NULL,NULL," fork: Resource temporarily unavailable",1);
			exit(g_data.status_code);
		}
		if (!pid)
		{
			tmp_write_pipe = fds[1];
			signals_for_child();
			get_fds(tmp_command->redir_in_out, &last_fd, &fds[1]);
			duplicate_fds(tmp, last_fd, fds, tmp_write_pipe);
			execute_command(tmp_command, get_my_path(tmp_command));
			exit(g_data.status_code);
		}
		else
		{
			pidd[i] = pid;
			if (last_fd != 0)
				close(last_fd);
			last_fd = fds[0];
			tmp = tmp->next;
			close(fds[1]);
			i++;
		}
	}
	
	closing_pipe(commands, pidd, i);
}
