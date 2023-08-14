/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:00:00 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 05:46:44 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multiple_pipe_init(t_exeec *z, t_commandes **c, char *list)
{
	z->pipe_fd[0] = -1;
	z->pipe_fd[1] = -1;
	z->t = count_last_inf_heredoc(list);
	z->cmd = *c;
	z->l = my_malloc(sizeof(t_varint));
	z->l->size = count_heredoc(list);
	z->l->pipe_fd[0] = -1;
	z->l->pipe_fd[1] = -1;
	z->s = ft_lst_size(*c);
	z->i = 0;
	z->l->fd_rdc = my_malloc(sizeof(int) * z->t);
	z->l->nb_h = 0;
	z->cp = NULL;
}

void	set_pipe(t_exeec *z, t_envar **ev)
{
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
		z->l->in = -1;
		z->l->out = -1;
		z->pid_fd[z->i] = fork();
		if (z->pid_fd[z->i] < 0)
		{
			printf("Minishel: error fork\n");
			return ;
		}
		else if (z->pid_fd[z->i] == 0 && z->cmd->commande[0])
			child_process_in_pipe(&z, ev);
		parent_process_in_pipe(&z);
	}
}

void	multiple_pipe(t_commandes **c, t_envar **ev, char *list, t_env **eev)
{
	t_exeec	z;

	if (list[0])
	{
		z.l->s = *eev;
		z.l->env = *ev;
		multiple_pipe_init(&z, c, list, ev);
		if (z.s == 1)
		{
			single_node_exec(&z, list, ev);
			return ;
		}
		else if (z.s > 1)
			if (bigger_than_one(*list, **c, &z))
				return ;
	}
	return ;
}
