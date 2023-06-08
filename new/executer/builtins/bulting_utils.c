/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:03:10 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/21 16:03:12 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	is_bultin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd",3))
		return (0);
	if (!ft_strncmp(cmd, "env",3))
		return (0);
	if (!ft_strncmp(cmd, "echo",4))
		return (0);
	if (!ft_strncmp(cmd, "unset",5))
		return (0);
	if (!ft_strncmp(cmd, "export",6))
		return (0);
	if (!ft_strncmp(cmd, "cd",2))
		return (0);
	if (!ft_strncmp(cmd, "exit",4))
		return (0);
	return (1);
}

int	execute_bultin(t_command *command, int outfile)
{
	if (!ft_strncmp(command->cmd, "env",3))
		return (ft_env(outfile));
	else if (!ft_strncmp(command->cmd, "echo",4))
		return (ft_echo(command));
	else if (!ft_strncmp(command->cmd, "unset",5))
		return (ft_unset(command));
	else if (!ft_strncmp(command->cmd, "export",6))
		return (ft_export(command, outfile));
	else if (!ft_strncmp(command->cmd, "cd",2))
		return (ft_cd(command));
	if (!ft_strncmp(command->cmd, "pwd",3))
		return (ft_pwd(command->cmd, outfile));
	if (!ft_strncmp(command->cmd, "exit",4))
		return (ft_exit(command));
	return (0);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if ((key[0] >= 'a' && key[0] <= 'z') || (key[0] >= 'A' && key[0] <= 'Z'))
		return (0);
	return (-1);
}

int	is_num(char *str)
{
	int i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (-1);
	}
	return (i);
}