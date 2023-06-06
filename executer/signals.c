/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:57:07 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/06 17:41:09 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	prompt(int sig)
{
	// g_data.status_code = 1;
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	signals_for_parent(void)
{
	// tcgetattr(STDIN_FILENO, &(g_data.newTerm));
	// g_data.oldTerm = g_data.newTerm;
	// g_data.newTerm.c_lflag &= ~ECHOCTL;
	// // ctl C 2
	// signal(SIGINT, prompt);
	// // ctl / 3
	// signal(SIGQUIT, SIG_IGN);
}

void	signals_for_child(void)
{
	// g_data.newTerm.c_lflag |= ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.newTerm));
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
}
