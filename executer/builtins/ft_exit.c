/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:30:49 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/05 10:30:54 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

void	set_status(int status)
{
	g_data.status_code = status;
	add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code), NULL);
}

int	check_err_exit(char *arg, char *cmd)
{
	if ((arg && is_num(arg) == -1))
		return (print_cmd_error(cmd, arg, "numeric argument required", 255));
	else
		return (0);
}

int	ft_exit(t_command *cmd)
{
	int				status;
	int				one_arg;
	unsigned char	test;
	int flag;

	status = 0;
	one_arg = 1;
	if (cmd->args[1])
	{
		status = check_err_exit(cmd->args[1], cmd->cmd);
		if (cmd->args && cmd->args[2] && !status)
		{
			one_arg = 0;
			status = print_cmd_error(cmd->cmd, NULL, "too many arguments", 1);
		}
		if (cmd->args[1] && is_num(cmd->args[1]) >= 0 && one_arg)
		{
			test = (unsigned char)ft_atoi(cmd->args[1],&flag);
			status = test;
		}
	}
	set_status(status);
	if (one_arg)
		exit(g_data.status_code);
	return (status);
}
