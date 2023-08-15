/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 06:12:13 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 06:17:57 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_z(t_exeec *z, t_commandes **c)
{
	z->cmd = *c;
	z->i = 0;
	z->old_ifd = 0;
	z->l->k = 0;
	z->l->nb_h = 0;
}

void	init_z_next(t_exeec *z)
{
	z->l->in = -1;
	z->l->out = -1;
	z->pid_fd[z->i] = fork();
}

int	bigger_than_one(char *list, t_commandes **c, t_exeec *z, t_envar **ev, char **envi)
{
	if (heredoc_in_multiple_pipe(c, list, z, envi))
		return (1);
	init_z(z, c);
	while (z->i < z->s)
	{
		if (z->i < z->s - 1)
		{
			z->m = pipe(z->pipe_fd);
			if (z->m < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		init_z_next(z);
		if (z->pid_fd[z->i] < 0)
		{
			printf("Minishel: error fork\n");
			return (1);
		}
		else if (z->pid_fd[z->i] == 0 && z->cmd->commande[0])
			child_process_in_pipe(z, ev);
		parent_process_in_pipe(z);
	}
	return (wait_child_and_signals(z), 0);
}