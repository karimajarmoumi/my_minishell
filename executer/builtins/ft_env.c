/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:26:15 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/09 16:28:25 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	preorder_traversal(t_node *head, int fd)
{
	if (head == NULL)
		return ;
	if (head->value)
	{
		write(fd, head->key, ft_strlen(head->key));
		write(fd, "=", 1);
		write(fd, head->value, ft_strlen(head->value));
		write(fd, "\n", 1);
	}
	preorder_traversal(head->left, fd);
	preorder_traversal(head->right, fd);
}

int	ft_env(int fd)
{
	int	status;

	preorder_traversal(g_data.env_vars, fd);
	status = 0;
	return (status);
}

char	*get_env(char *key)
{
	t_node	*node;

	node = get_node(g_data.env_vars, key);
	if (node)
		return (node->value);
	return (NULL);
}

char	**store_envs(t_node *head, char **envs, int *i)
{
	int	len_key;
	int	len_value;
	int	j;
	int	k;

	if (!head)
		return (envs);
	len_key = ft_strlen(head->key);
	len_value = ft_strlen(head->value);
	envs[*i] = malloc((len_key + len_value + 2) * sizeof(char));
	if (!envs[*i])
		return (NULL);
	j = 0;
	while (j < len_key)
	{
		envs[*i][j] = head->key[j];
		j++;
	}
	envs[*i][j] = '=';
	j++;
	k = 0;
	while (j < len_key + len_value + 1)
	{
		envs[*i][j] = head->value[k];
		k++;
		j++;
	}

	envs[*i][j] = '\0';
	(*i)++;
	envs = store_envs(head->left, envs, i);
	envs = store_envs(head->right, envs, i);
	return (envs);
}
