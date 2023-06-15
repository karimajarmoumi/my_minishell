/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/15 12:35:29 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*get_right_path(char *cmd, t_command *data)
{
	int		i;
	char	*absolute_path;
	char	*env;
	char	**paths;

	i = 0;
	env = get_env("PATH");
	if (!env)
		g_data.status_code = print_cmd_error(cmd, NULL,
				"No such file or directory", 127);
	paths = ft_split(env, ':');
	absolute_path = NULL;
	cmd = ft_strjoin("/", cmd);
	while (paths[i])
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

char	*get_actual_path(char *cmd, t_command *data)
{
	int	status;

	status = 127;
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		status = 126;
	}
	return (get_right_path(cmd, data));
}
