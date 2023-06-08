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

	i = 0;
	while (envs[i])
	{
		pos = find_char(envs[i], '=');
		key = ft_substr(envs[i], 0, pos);
		value = ft_substr(envs[i], pos + 1, ft_strlen(envs[i]));
		add_node(&(g_data.env_vars), key, value, NULL);
		free(key);
		free(value);
		i++;
	}
}

void	initilizer(char **envs)
{
	bzero(&g_data, sizeof(t_data));
	init_envs(envs);
}
