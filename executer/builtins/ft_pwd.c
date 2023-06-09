/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:57:06 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/23 13:57:08 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	ft_pwd(char *cmd, int fd)
{
	char	buff[1024];
	int		status;

	status = 0;
	if (!getcwd(buff, sizeof(buff)))
		return (print_cmd_error(cmd, NULL, strerror(errno), 1));
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	return (status);
}
