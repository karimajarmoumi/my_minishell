/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:03:10 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 18:19:26 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_bultin(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (0);
	if (!ft_strcmp(cmd, "env"))
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (0);
	if (!ft_strcmp(cmd, "unset"))
		return (0);
	if (!ft_strcmp(cmd, "export"))
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
}

int	execute_bultin(t_command *command, int outfile)
{
	if (!ft_strcmp(command->cmd, "env"))
		return (ft_env(outfile));
	else if (!ft_strcmp(command->cmd, "echo"))
		return (ft_echo(command, outfile));
	else if (!ft_strcmp(command->cmd, "unset"))
		return (ft_unset(command));
	else if (!ft_strcmp(command->cmd, "export"))
		return (ft_export(command, outfile));
	else if (!ft_strcmp(command->cmd, "cd"))
		return (ft_cd(command));
	if (!ft_strcmp(command->cmd, "pwd"))
		return (ft_pwd(command->cmd, outfile));
	if (!ft_strcmp(command->cmd, "exit"))
		return (ft_exit(command));
	return (0);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key[0])
		return (-1);
	while (key && key[i])
	{
		if (i == 0)
		{
			if (!ft_isalpha(key[i]) && key[i] != '_')
				return (-1);
		}
		else
			if (!ft_isalnum(key[i]) && key[i] != '_' )
				return (-1);
		i++;
	}
	return (0);
}

int	is_num(char *str)
{
	int	i;
	int	flag;
	int	test;

	flag = 0;
	i = 0;
	test = ft_atoi(str, &flag);
	if (flag == 1)
		return (-1);
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
