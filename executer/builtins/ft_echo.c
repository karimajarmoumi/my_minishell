/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:05:08 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/15 18:59:06 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (-1);
			i++;
		}
	}
	else
		i = -1;
	return (i);
}

int	ft_echo(t_command *command, int fd)
{
	int	i;
	int	option;
	int	start;

	i = 1;
	option = 0;
	if (!command->args[1])
		write(fd, "\n", 1);
	while (command->args[i] && check_option(command->args[i]) != -1)
	{
		option = 1;
		i++;
	}
	start = i;
	while (command->args[i])
	{
		if (i != start)
			printf(" ");
		write(fd, command->args[i], ft_strlen(command->args[i]));
		i++;
	}
	if (!option)
		write(fd, "\n", 1);
	return (0);
}
