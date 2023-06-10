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

void	add_new_value(int pos, char *arg, char **value, char **key)
{
	char	*new_value;
	char	*old_value;

	*key = ft_substr(arg, 0, pos - 1);
	old_value = get_env(*key);
	new_value = ft_substr(arg, pos + 1, ft_strlen(arg));
	if (!old_value)
		old_value = ft_strdup("");
	*value = ft_strjoin(old_value, new_value);
}
int	add_new_element(t_command *cmd)
{
	int		i;
	int		pos;
	char	*key;
	char	*value;
	int		status;
	int		flag;

	flag = 0;
	status = 0;
	i = 1;
	while (cmd->args && cmd->args[i])
	{
		pos = find_char(cmd->args[i], '=');
		if (cmd->args[i][pos - 1] == '+')
			flag = 1;
		if (pos == -1)
		{
			key = cmd->args[i];
			value = NULL;
		}
		key = ft_substr(cmd->args[i], 0, pos);
		value = ft_substr(cmd->args[i], pos + 1, ft_strlen(cmd->args[i]));
		if (is_valid_key(key) == -1)
		{
			status = print_cmd_error(cmd->cmd, key, "not a valid identifier",
					1);
			i++;
			continue ;
		}
		if (flag)
			add_new_value(pos, cmd->args[i], &value, &key);
		add_node(&(g_data.env_vars), key, value, NULL);
		ft_free(key);
		ft_free(value);
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
