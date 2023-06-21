/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:57:07 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/19 21:42:04 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt(int sig)
{
	(void)sig;
	g_data.status_code = 1;
	printf("\n");
	if (!g_data.isChild)
	{
		// rl_on_new_line();
		//  rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	signals_for_parent(void)
{
	tcgetattr(STDIN_FILENO, &(g_data.new_term));
	g_data.old_term = g_data.new_term;
	g_data.new_term.c_lflag &= ~ECHOCTL;
	signal(SIGINT, prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_for_child(void)
{
	g_data.new_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.new_term));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
