/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:28:10 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/20 15:39:35 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_status_code(void)
{
	char	*status;

	status = ft_itoa(g_data.status_code);
	add_node(&(g_data.env_vars), "?", status, NULL);
	ft_free(status);
}

void	add_essential_envs(void)
{
	add_node(&(g_data.env_vars), "SHLVL", "1", NULL);
	add_node(&(g_data.env_vars), "PWD", get_working_dir(), NULL);
	add_node(&(g_data.env_vars), "_", "/usr/bin/env", NULL);
}

void	init_envs(char **envs)
{
	int		i;
	char	*key;
	char	*value;
	int		pos;

	i = -1;
	if (!*envs)
		add_essential_envs();
	while (envs[++i])
	{
		pos = searching_for_char(envs[i], '=');
		key = ft_substr(envs[i], 0, pos);
		if (!ft_strcmp(key, "OLDPWD"))
		{
			ft_free(key);
			continue ;
		}
		value = ft_substr(envs[i], pos + 1, ft_strlen(envs[i]));
		add_node(&(g_data.env_vars), key, value, NULL);
		my_free(value, key);
	}
	store_status_code();
}

char	*initilizer(char **envs, int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_bzero(&g_data, sizeof(t_data));
	get_working_dir();
	init_envs(envs);
	signals_for_parent();
	return (NULL);
}
