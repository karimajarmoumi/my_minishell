/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:27:09 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 19:02:00 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// final version
#include "../../minishell.h"

void	inorder_traversal(t_node *head, int fd)
{
	char	qoute;

	if (head == NULL)
		return ;
	if (!ft_strncmp(head->key, "?", ft_strlen(head->key)))
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
	char 	*tmp;

	tmp = *key;
	*key = ft_substr(arg, 0, pos - 1);
	ft_free(tmp);
	old_value = get_env(*key);
	new_value = ft_substr(arg, pos + 1, ft_strlen(arg));
	if (!old_value)
		old_value = ft_strdup("");
	tmp = *value;
	*value = ft_strjoin(old_value, new_value);
	ft_free(tmp);
}

void	test(char **arg, int *pos, int *flag, int i)
{
	*pos = searching_for_char(arg[i], '=');
	if (arg[i] && *pos > 0 && arg[i][*pos - 1] == '+')
		*flag = 1;
}

int	add_new_element(t_command *cmd)
{
	int		i;
	int		pos;
	char	*key;
	char	*value;
	int		flag;

	key = ft_strdup("");
	init_value(&pos, &flag, &i, &g_data.status_code);
	while (cmd->args && cmd->args[++i])
	{
		test(cmd->args, &pos, &flag, i);
		if (pos == -1)
		{
			key = ft_strdup(cmd->args[i]);
			value = ft_strdup("");
		}
		if (!flag && pos > 0)
			key = ft_substr(cmd->args[i], 0, pos);
		else
			key = ft_strdup(cmd->args[i]);
		if (pos >= 0)
			value = ft_substr(cmd->args[i], pos + 1, ft_strlen(cmd->args[i]));
		if (flag)
			add_new_value(pos, cmd->args[i], &value, &key);
		if (!check_err_export(cmd->args[i],key, cmd->cmd))
			add_node(&(g_data.env_vars), key, value, NULL);
		my_free(value, key);
	}
	return (g_data.status_code);
}

int	ft_export(t_command *command, int fd)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	if (command->args && command->args[i])
	{
		status = add_new_element(command);
	}
	else
		inorder_traversal(g_data.env_vars, fd);
	return (status);
}
