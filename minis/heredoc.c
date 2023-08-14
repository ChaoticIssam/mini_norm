/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:51:55 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 05:33:20 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_heredoc(t_herdc *a, t_varint *l)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	a->i = 0;
	while (1)
	{
		l->line = readline(">");
		a->tmp = l->line;
		a->tmp = check_bill_her(a->tmp, l->s, l->env);
		l->line = a->tmp;
		fill_sring(l, a);
		a->i++;
	}
	exit(0);
}

int	handle_heredoc(t_herdc *a, t_varint *l)
{
	if (a->pid[a->j] < 0)
	{
		printf("Minishel: error fork\n");
		return (-1);
	}
	if (a->pid[a->j] == 0)
		child_heredoc(a, l);
	else
	{
		if (parent_heredoc(a, l) == -1)
			return (-1);
	}
	l->x++;
	a->j++;
	a->o += 2;
	return (0);
}

int	heredoc(t_commandes **c, t_varint *l, char *list)
{
	t_herdc	a;

	init_hered_var(&a, c, l, list);
	while (list[a.o])
	{
		if (list[a.o] == '8' && list[a.o + 1] && list[a.o + 1] == '8')
		{
			if (l->tmp->files[l->x] && !ft_strcmp(a.in_file,
					l->tmp->files[l->x]))
			{
				a.m = pipe(l->pipe_fd);
				if (a.m < 0)
					exit(EXIT_FAILURE);
				l->fd_rdc[l->nb_h] = l->pipe_fd[0];
			}
			a.pid[a.j] = fork();
			if (handle_heredoc(&a, l) == (-1))
				return (-1);
		}
		else
			a.o++;
	}
	return (0);
}
