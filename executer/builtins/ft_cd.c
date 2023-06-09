/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:04:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/24 15:04:53 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	ft_cd(t_command *command)
{
	char	old_pwd[1024];
	char	current_pwd[1024];
	char	*target;
	char	*prev;
	char	*home;

	if (command->args[1] && command->args[1][0] == '~')
		command->args[1] = ft_strjoin(HOME, &command->args[1][1]);
	if (command->args[1] && command->args[1][0] == '-')
	{
		prev = get_env("OLDPWD");
		if (!prev)
			return (print_cmd_error(command->cmd, NULL, "OLDPWD not set", 1));
		command->args[1] = prev;
		printf("%s\n", command->args[1]);
	}
	if (!command->args[1])
	{
		home = get_env("HOME");
		if (!home)
			return (print_cmd_error(command->cmd, NULL, "HOME not set", 1));
		command->args[1] = home;
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (print_cmd_error(command->cmd, command->args[1], strerror(errno),
				1));
	if (chdir(command->args[1]) != 0)
		return (print_cmd_error(command->cmd, command->args[1], strerror(errno),
				1));
	if (!getcwd(current_pwd, sizeof(current_pwd)))
		return (print_cmd_error(command->cmd, command->args[1], strerror(errno),
				1));
	add_node(&g_data.env_vars, "OLDPWD", old_pwd, NULL);
	add_node(&g_data.env_vars, "PWD", current_pwd, NULL);
	return (0);
}
