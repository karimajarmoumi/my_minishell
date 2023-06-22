/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:57:06 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/22 15:16:58 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_working_dir(void)
{
	char	*path;
	char	*tmp;

	tmp = g_data.current_dir;
	path = getcwd(NULL, 1024);
	if (path && *path)
	{
		g_data.current_dir = path;
		ft_free(tmp);
	}
	return (g_data.current_dir);
}

int	ft_pwd(char *cmd, int fd)
{
	char	*buff;
	int		status;

	(void)cmd;
	status = 0;
	buff = get_working_dir();
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	return (status);
}
