/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:08:58 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/18 16:09:02 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_err_export(char *arg, char *key, char *cmd)
{
	if (is_valid_key(key) == -1)
	{
		g_data.status_code = print_cmd_error(cmd, arg, "not a valid identifier",
				1);
		return (-1);
	}
	return (0);
}

void	init_value(int *pos, int *flag, int *i, int *status)
{
	*pos = 0;
	*flag = 0;
	*i = 0;
	*status = 0;
}

void	my_free(char *value, char *key)
{
	ft_free(key);
	ft_free(value);
}
