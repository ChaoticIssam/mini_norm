/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:57:21 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 03:35:59 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_in_multiple_pipe(t_commandes **c, char *list, t_exeec *z)
{
	z->pid_fd = my_malloc(sizeof(int) * z->s);
	z->list_sp = ft_split(list, '6');
	z->cmd = *c;
	z->l->k = 0;
	z->l->nb_h = 0;
	if (z->cmd->files)
	{
		while (z->list_sp[z->l->k])
		{
			if (heredoc(&z->cmd, z->l, z->list_sp[z->l->k]) == -1)
			{
				close(z->l->pipe_fd[1]);
				break ;
			}
			z->l->k++;
			z->cmd = z->cmd->next;
		}
	}
	if (g_g.exit_status == 1)
		return (1);
	return (0);
}

void	redirection_for_first_command(t_exeec *z)
{
	close(z->pipe_fd[0]);
	if (z->l->in != -1)
	{
		dup2(z->l->in, 0);
		close(z->l->in);
	}
	if (z->l->out != -1)
	{
		dup2(z->l->out, 1);
		close(z->l->out);
	}
	else
		dup2(z->pipe_fd[1], 1);
}

void	redirection_for_midle_command(t_exeec *z)
{
	if (z->l->out != -1)
	{
		dup2(z->l->out, 1);
		close(z->l->out);
	}
	else
	{
		dup2(z->pipe_fd[1], 1);
		close(z->pipe_fd[1]);
	}
	if (z->l->in != -1)
	{
		dup2(z->l->in, 0);
		close(z->l->in);
	}
	else
	{
		dup2(z->old_ifd, 0);
		close(z->old_ifd);
	}
}

void	redirection_for_last_command(t_exeec *z)
{
	if (z->l->out != -1)
	{
		dup2(z->l->out, 1);
		close(z->l->out);
	}
	if (z->l->in != -1)
	{
		dup2(z->l->in, 0);
		close(z->l->in);
	}
	else
	{
		dup2(z->old_ifd, 0);
		close(z->old_ifd);
	}
}
