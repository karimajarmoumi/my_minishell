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

int	ft_exit(t_command *command)
{
	int				status;
	int				one_arg;
	unsigned char	test;

	status = 0;
	one_arg = 1;
	printf("exit\n");
	if (command->args[1])
	{
		if ((command->args[1] && is_num(command->args[1]) == -1)
			|| ft_atoi(command->args[1]) == -1
			|| ft_atoi(command->args[1]) == 0)
			status = print_cmd_error(command->cmd, command->args[1],
					"numeric argument required", 255);
        //exit g
		if (command->args && command->args[2] && !status)
		{
			one_arg = 0;
			status = print_cmd_error(command->cmd, NULL, "too many arguments",
					1);
		}
		if (command->args[1] && is_num(command->args[1]) >=0 && one_arg)
		{
			test = (unsigned char)ft_atoi(command->args[1]);
			status = test;
		}
	}
	g_data.status_code = status;
    add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code),NULL);
    if(one_arg)
	    exit(g_data.status_code);
	return (status);
}

//exit num
//exit alone
//exit hhhh
