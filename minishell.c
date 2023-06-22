/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/22 20:02:28 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*commands;
	char	*line;

	line = initilizer(env, ac, av);
	while (1)
	{
		ft_free(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.new_term));
		line = readline(" 🌸 beautiful as a shell : 🌸 $ ");
		if (line)
		{
			if (!ft_strlen(line) || !ft_strncmp(line, "\n", 2))
				continue ;
			add_history(line);
			commands = parser(line);
			if (commands)
			{
				executer(commands);
				free_commands(commands);
			}
		}
		else
			exit(g_data.status_code);
	}
	return (0);
}
