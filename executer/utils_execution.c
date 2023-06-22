/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:26:53 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/22 14:26:56 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		g_data.isChild = 0;
		store_status_code();
	}
}

void	execute_command(t_command *tmp_command, char *path)
{
	char	**envs;
	int		status;

	status = 127;
	if (!is_bultin(tmp_command->cmd))
	{
		g_data.status_code = execute_bultin(tmp_command, 1);
		return ;
	}
	else
	{
		envs = convert_tree_to_array();
		if (execve(path, tmp_command->args, envs) == -1)
			exit(status);
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
