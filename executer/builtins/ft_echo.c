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
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (i);
}

int	ft_echo(t_command *command)
{
	int	i;
	int	option;
	int	start;

	i = 1;
	option = 0;
	if (!command->args[1])
		printf("\n");
	while (command->args && check_option(command->args[i]) != -1)
	{
		option = 1;
		i++;
	}
	start = i;
	while (command->args[i])
	{
		//printf("%s\n",command->args[i]);
		if (i != start)
			printf(" ");
		printf("%s", command->args[i]);
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
