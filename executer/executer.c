/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:18 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/06 17:40:50 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
void	execute_command(t_command *tmp_command, char *path)
{
	char	**envs;

	if (!is_bultin(tmp_command->cmd))
	{
		g_data.status_code = execute_bultin(tmp_command, 1);
		return ;
	}
	else
	{
		char **envs=convert_tree_to_array();
		if (execve(path, tmp_command->args, envs) == -1)
			exit(127);
	}
}

void	closing_pipe(t_list *commands, int *fd, int *pidd, int i)
{
	int	j;
	int	status;

	j = 0;
	if (commands)
	{
		while (j < i)
		{
			close(fd[j]);
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
	}
}

char	*get_my_path(t_command *tmp_command)
{
	char	*path;

	if (!(tmp_command->cmd))
		exit(0);
	if (is_bultin(tmp_command->cmd))
	{
		path = get_actual_path(tmp_command->cmd, tmp_command);
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
		if (  tmp_command->cmd && (!strcmp(tmp_command->cmd, "unset") || !strcmp(tmp_command->cmd,
					"export") || !strcmp(tmp_command->cmd, "cd")
				|| !strcmp(tmp_command->cmd, "exit")))
		{
			get_inputfile_fd(&infile, tmp_command->redir_in, 1, 0);
			get_outfile_fd(&outfile, tmp_command->redir_out);

			g_data.status_code=execute_bultin(tmp_command, outfile);

			return g_data.status_code;

		}
	}
	return (-1);
}

void	executer(t_list *commands)
{
	int			fds[2];
	t_list		*tmp;
	int			fd[1024];
	int			pidd[1000];
	int			i;
	t_command	*tmp_command;
	int			pid;
	int			last_fd;

	tmp = commands;
	i = 0;
	last_fd = STDIN_FILENO;
	if (run_builtins(tmp) >= 0)
		return ;
	while (tmp)
	{
		tmp_command = (t_command *)tmp->content;
		if (pipe(fds) == -1)
			print_cmd_error(tmp_command->cmd, tmp_command->args[1],
					strerror(errno), 1);
		pid = fork();
		if (!pid)
		{
			signals_for_child();
			get_inputfile_fd(&last_fd, tmp_command->redir_in, fds[1], fds[0]);
			get_outfile_fd(&fds[1], tmp_command->redir_out);
			duplicate_fds(tmp, last_fd, fds);
			execute_command(tmp_command, get_my_path(tmp_command));
			exit(g_data.status_code);
		}
		else
		{
			pidd[i] = pid;
			fd[i] = fds[0];
			last_fd = fds[0];
			tmp = tmp->next;
			close(fds[1]);
			i++;
		}
	}
	closing_pipe(commands, fd, pidd, i);
}
