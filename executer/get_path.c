/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 21:41:03 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_err_path(char *cmd)
{
	g_data.status_code = print_cmd_error(cmd, NULL, "No such file or directory",
			127);
	exit(g_data.status_code);
}

char	*get_right_path(char *cmd)
{
	int		i;
	char	*absolute_path;
	char	*env;
	char	**paths;

	i = 0;
	env = get_env("PATH");
	if (!env)
		check_err_path(cmd);
	paths = ft_split(env, ':');
	absolute_path = NULL;
	cmd = ft_strjoin("/", cmd);
	while (paths && paths[i])
	{
		absolute_path = ft_strjoin(paths[i], cmd);
		if (!access(absolute_path, F_OK | X_OK))
			break ;
		free(absolute_path);
		absolute_path = NULL;
		i++;
	}
	if (!absolute_path)
		g_data.status_code = 127;
	return (absolute_path);
}

char	*get_actual_path(char *cmd)
{
	int	status;

	status = 127;
	if (ft_strchr(cmd, '/') && access(cmd, F_OK))
	{
		print_cmd_error(cmd, NULL, strerror(errno), status);
		exit(status);
	}
	if (!access(cmd, F_OK))
	{
		if (opendir(cmd))
		{
			print_cmd_error(cmd, NULL, "is a directory", 126);
			exit(126);
		}
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		else if (!access(cmd, X_OK))
		{
			print_cmd_error(cmd, NULL, strerror(errno), 1);
			exit(1);
		}
	}
	return (get_right_path(cmd));
}
