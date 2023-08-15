/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:09:25 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 01:36:56 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "readline.h"

static void	control_c(int sig)
{
	if (sig == SIGINT)
	{
		if (g_g.readline)
		{
			g_g.exit_status = 1;
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	sig_quit(int sig)
{
	(void)sig;
	if (g_g.child)
		printf("Quit: 3\n");
	rl_redisplay();
}

void	signal_handler(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, sig_quit);
}
