/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:03:44 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/31 16:03:47 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	add_child_to_parent(t_node *node, t_node *child_node)
{
	t_node	*node_parent;

	node_parent = node->parent;
	if (node_parent)
	{
		if (node_parent->right == node)
			node_parent->right = child_node;
		else
			node_parent->left = child_node;
	}
}

void	switch_nodes(t_node *node_1, t_node *node_2)
{
	add_child_to_parent(node_1, NULL);
	node_1->parent = node_2->parent;
	node_1->left = node_2->left;
	node_1->right = node_2->right;
	add_child_to_parent(node_2, node_1);
}

void	remove_node(t_node **head, char *key)
{
	t_node	*to_delete_node;
	t_node	*new_root;
	t_node	*min_node;

	if (!head)
		return ;
	to_delete_node = get_node(*head, key);
	if (!to_delete_node || (to_delete_node->key && !ft_strncmp(to_delete_node->key,
				"?",1)))
		return ;
	if (to_delete_node->right == NULL && to_delete_node->left == NULL)
	{
		add_child_to_parent(to_delete_node, NULL);
		new_root = NULL;
	}
	else if (to_delete_node->right == NULL)
	{
		add_child_to_parent(to_delete_node, to_delete_node->left);
		new_root = to_delete_node->left;
	}
	else if (to_delete_node->left == NULL)
	{
		add_child_to_parent(to_delete_node, to_delete_node->right);
		new_root = to_delete_node->right;
	}
	else
	{
		min_node = get_most_left(to_delete_node->right);
		switch_nodes(min_node, to_delete_node);
		new_root = min_node;
	}
	if (*head == to_delete_node)
		*head = new_root;
	free_node(&to_delete_node);
	g_data.count_envs--;
}
