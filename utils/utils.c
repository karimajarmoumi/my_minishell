/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:30:15 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/18 20:09:01 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_cmd_error(char *cmd, char *args, char *msg_err, int status_code)
{
	char	*my_shell;

	my_shell = "my_shell";
	write(STDERR_FILENO, my_shell, ft_strlen(my_shell));
	write(STDERR_FILENO, ": ", 2);
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	if (args)
	{
		write(STDERR_FILENO, args, ft_strlen(args));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, msg_err, ft_strlen(msg_err));
	write(STDERR_FILENO, "\n", 1);
	g_data.status_code = status_code;
	return (status_code);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		if (*ptr)
		{
			while (ptr[i])
			{
				free(ptr[i]);
				ptr[i] = NULL;
				i++;
			}
			free(ptr);
		}
	}
}

int	searching_for_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_node(t_node **node)
{
	if (!node || !*node)
		return ;
	ft_free((*node)->key);
	ft_free((*node)->value);
	(*node)->key = NULL;
	(*node)->value = NULL;
	(*node)->parent = NULL;
	(*node)->left = NULL;

	ft_free(*node);
	*node = NULL;
}
