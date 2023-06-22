/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:04:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 15:06:40 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_old_position(char **arg, char *cmd)
{
	char	*prev;
	char	*tmp;

	prev = get_env("OLDPWD");
	if (!prev)
		return (print_cmd_error(cmd, NULL, "OLDPWD not set", 1));
	tmp = *arg;
	*arg = ft_strdup(prev);
	ft_free(tmp);
	printf("%s\n", *arg);
	return (0);
}

char	*get_home_positin(char *cmd)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
		print_cmd_error(cmd, NULL, "HOME not set", 1);
	return (home);
}

int	ft_cd(t_command *cmd)
{
	char	*old_pwd;
	char	*path;
	char	*home;

	path = ft_strdup(cmd->args[1]);
	if (path && path[0] == '-' && ft_strlen(path) == 1)
	{
		if (get_old_position(&path, cmd->cmd) == 1)
			return (1);
	}
	if (!path)
	{
		home = get_home_positin(cmd->cmd);
		if (!home || !home[0])
			return (1);
		path = ft_strdup(home);
	}
	if (chdir(path) != 0)
		return (print_cmd_error(cmd->cmd, cmd->args[1], strerror(errno), 1));
	old_pwd = get_env("PWD");
	add_node(&g_data.env_vars, "OLDPWD", old_pwd, NULL);
	if (old_pwd)
		add_node(&g_data.env_vars, "PWD", get_working_dir(), NULL);
	ft_free(path);
	return (0);
}
