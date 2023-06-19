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

	prev = get_env("OLDPWD");
	if (!prev)
		return (print_cmd_error(cmd, NULL, "OLDPWD not set", 1));
	*arg = prev;
	printf("%s\n", *arg);
	return (0);
}

int	get_home_positin(char **arg, char *cmd)
{
	char	*home;

	home = get_env("HOME");
	if (!home)
		return (print_cmd_error(cmd, NULL, "HOME not set", 1));
	*arg = home;
	return (0);
}

int	ft_cd(t_command *cmd)
{
	char	old_pwd[1024];
	char	current_pwd[1024];

	if (cmd->args[1] && cmd->args[1][0] == '~')
		cmd->args[1] = ft_strjoin(HOME, &cmd->args[1][1]);
	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		if (get_old_position(&cmd->args[1], cmd->cmd) == 1)
			return (1);
	}
	if (!cmd->args[1])
	{
		if (get_home_positin(&cmd->args[1], cmd->cmd) == 1)
			return (1);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (print_cmd_error(cmd->cmd, cmd->args[1], strerror(errno), 1));
	if (chdir(cmd->args[1]) != 0)
		return (print_cmd_error(cmd->cmd, cmd->args[1], strerror(errno), 1));
	if (!getcwd(current_pwd, sizeof(current_pwd)))
		return (print_cmd_error(cmd->cmd, cmd->args[1], strerror(errno), 1));
	add_node(&g_data.env_vars, "OLDPWD", old_pwd, NULL);
	add_node(&g_data.env_vars, "PWD", current_pwd, NULL);
	return (0);
}
