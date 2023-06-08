/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:27:09 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/18 16:27:11 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

//final version

void	inorder_traversal(t_node *head, int fd)
{
	char	qoute;

	if (head == NULL)
		return ;
	qoute = '"';
	inorder_traversal(head->left, fd);
	if (!head->value)
	{
		write(fd, "declare -x ", 11);
		write(fd, head->key, ft_strlen(head->key));
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, "declare -x ", 11);
		write(fd, head->key, ft_strlen(head->key));
		write(fd, "=", 1);
		write(fd, &qoute, 1);
		write(fd, head->value, ft_strlen(head->value));
		write(fd, &qoute, 1);
		write(fd, "\n", 1);
	}
	inorder_traversal(head->right, fd);
}

int	add_new_element(t_command *command)
{
	int		i;
	int		pos;
	char	*key;
	char	*value;
	int		status;

	status = 0;
	i = 1;
	while (command->args && command->args[i])
	{
	
		pos = find_char(command->args[i], '=');
		if (pos == -1 && is_valid_key(command->args[i]) == -1)
		{
			status = print_cmd_error(command->cmd, command->args[i], "not a valid identifier1", 1);
			i++;
			continue ;
		}
		if (pos != -1)
		{
			key = ft_substr(command->args[i], 0, pos);

			if (is_valid_key(key) == -1)
			{
				status = print_cmd_error(command->cmd, key, "not a valid identifier2", 1);
				i++;
				continue ;
			}
			value = ft_substr(command->args[i], pos + 1,
					ft_strlen(command->args[i]));
			add_node(&(g_data.env_vars), key, value, NULL);
			ft_free(key);
			ft_free(value);
		}
		else
			add_node(&(g_data.env_vars), command->args[i], NULL, NULL);
		i++;
	}
	return (status);
}

int	ft_export(t_command *command, int fd)
{
	int	i;
	int	status;

	i = 1;
	if (command->args && command->args[i])
	{
		status = add_new_element(command);

	}
	else
		inorder_traversal(g_data.env_vars, fd);
	return (status);
}
