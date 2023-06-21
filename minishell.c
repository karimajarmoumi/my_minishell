/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/19 01:06:07 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_tree_to_array(void)
{
	int		p;
	char	**envs;
	char	**store;

	p = 0;
	envs = malloc(sizeof(char *) * (g_data.count_envs + 1));
	store = store_envs(g_data.env_vars, envs, &p);
	envs[p] = NULL;
	return (envs);
}

int	main(int ac, char **av, char **env)
{
	t_list	*commands;
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	initilizer(env);
	signals_for_parent();
	while (1)
	{
		if (line)
			ft_free(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.new_term));
		line = readline(PERPOL " 🌸 beautiful as a shell : 🌸 $ " RESET);
		if (line)
		{
			if (!ft_strlen(line) || !ft_strncmp(line, "\n", 2))
				continue ;
			add_history(line);
			commands = parser(line);
			if (commands)
			{
				executer(commands);
				add_node(&(g_data.env_vars), "?", ft_itoa(g_data.status_code),
					NULL);
				 free_commands(commands);
			}
		}
		else
			exit(g_data.status_code);

		
	}
	return (0);
}
