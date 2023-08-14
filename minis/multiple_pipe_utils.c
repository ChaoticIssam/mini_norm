/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:35:23 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 05:46:50 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell"

void	init_z(t_exeec *z)
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

int	bigger_than_one(char *list, t_commandes **c, t_exeec *z, t_envar **ev)
{
	if (heredoc_in_multiple_pipe(c, list, &z))
		return (1);
	init_z(z);
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