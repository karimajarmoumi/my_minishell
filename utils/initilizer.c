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
void	init_envs(char **envs)
{
	int		i;
	char	*key;
	char	*value;
	int		pos;
	char	buff[1024];

	i = 0;
	if (!*envs)
	{
		add_node(&(g_data.env_vars), "SHLVL", "1", NULL);
		add_node(&(g_data.env_vars), "PWD", getcwd(buff, sizeof(buff)), NULL);
		add_node(&(g_data.env_vars), "_", "/usr/bin/env", NULL);
	}
	while (envs[i])
	{
		pos = searching_for_char(envs[i], '=');
		key = ft_substr(envs[i], 0, pos);
		if (!ft_strcmp(key, "OLDPWD") && ++i)
		{
			ft_free(key);
			continue ;
		}
		value = ft_substr(envs[i], pos + 1, ft_strlen(envs[i]));
		add_node(&(g_data.env_vars), key, value, NULL);
		my_free(value, key);
		i++;
	}
	add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code), NULL);
}

void	initilizer(char **envs)
{
	ft_bzero(&g_data, sizeof(t_data));
	get_working_dir();
	init_envs(envs);
}
