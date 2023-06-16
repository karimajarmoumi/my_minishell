/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/16 17:46:21 by kjarmoum         ###   ########.fr       */
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
void free_red(t_list *redir_list)
{
	t_list *tmp_redir_list;
	t_list *next;
	t_red *tmp_red;

	tmp_redir_list=redir_list;
	while(tmp_redir_list)
	{
		tmp_red=(t_red*)tmp_redir_list->content;
		if(tmp_red)
			ft_free(tmp_red->file_name);
		next=tmp_redir_list->next;
		ft_free(tmp_redir_list);
		tmp_redir_list=next;
	}
}
void free_commands(t_list *commands)
{
	t_list *tmp_commands;
	t_command *cmd;
	t_list  *next;
	tmp_commands=commands;
	while(tmp_commands)
	{
		cmd=(t_command*)tmp_commands->content;
		ft_free(cmd->cmd);
		//free_double_ptr(cmd->args);
		free_red(cmd->redir_in);
		free_red(cmd->redir_out);
		ft_free(cmd);
		next=tmp_commands->next;
		ft_free(tmp_commands);
		tmp_commands=next;
	}
}
int	main(int ac, char **av, char **env)
{
	t_list		*commands;
	(void)ac;
	(void)av;
	char		*line;
	int			flg_err;

	line = NULL;
	initilizer(env);
	//signals_for_parent();
		flg_err = 0;
	while (1)
	{
		if (line)
			ft_free(line);
		//tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.new_term));
		line = readline(PERPOL " 🌸 beautiful as a shell : 🌸 $ " RESET);
		if (line)
		{
			if (!ft_strlen(line) || !ft_strncmp(line, "\n", 2))
				continue ;
			add_history(line);
			commands = parser(line, &flg_err);
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
