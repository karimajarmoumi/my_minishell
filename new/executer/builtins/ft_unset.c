/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:27:27 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/18 16:27:29 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"
//final version
int	ft_unset(t_command *command)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (command->args && command->args[i])
	{
		if (is_valid_key(command->args[i]) == -1)
		{
			status = print_cmd_error(command->cmd, command->args[i],
					"not a valid identifier", 1);
			i++;
			continue ;
		}
		// is this write right or not 
		remove_node(&(g_data.env_vars), command->args[i]);
		i++;
	}
	return (status);
}
