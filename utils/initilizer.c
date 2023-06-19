/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:28:10 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/18 16:28:12 by kel-baam         ###   ########.fr       */
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
		value = ft_substr(envs[i], pos + 1, ft_strlen(envs[i]));
		add_node(&(g_data.env_vars), key, value, NULL);
		ft_free(key);
		ft_free(value);
		i++;
	}
	add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code), NULL);
}

void	initilizer(char **envs)
{
	ft_bzero(&g_data, sizeof(t_data));
	init_envs(envs);
}
