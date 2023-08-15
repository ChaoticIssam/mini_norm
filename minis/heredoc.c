/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:51:55 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 03:07:47 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "readline.h"

void	init_hered_var(t_herdc *a, t_commandes **c, t_varint *l, char *list)
{
	a->m = -1;
	a->k = NULL;
	a->pid = my_malloc (sizeof(int) * l->size);
	l->tmp = (*c);
	a->i = 0;
	l->x = 0;
	a->j = 0;
	a->o = 0;
	a->in_file = get_first_infile(l->tmp->files, list);
}

int	parent_heredoc(t_herdc *a, t_varint *l)
{
	close(l->pipe_fd[1]);
	waitpid(a->pid[a->j], &(a->heredoc_status), 0);
	if (l->tmp->files[l->x] && !ft_strcmp(a->in_file, l->tmp->files[l->x]))
		l->nb_h++;
	if (WEXITSTATUS(a->heredoc_status))
	{
		g_g.exit_status = 1;
		return (-1);
	}
	return (0);
}

void	fill_sring(t_varint *l, t_herdc *a)
{
	if (l->tmp->files[l->x] && !ft_strcmp(l->line, l->tmp->files[l->x]))
	{
		if (!ft_strcmp(a->in_file, l->tmp->files[l->x]))
		{
			if (!a->m)
			{
				write(l->pipe_fd[1], a->k, ft_strlen(a->k));
				close(l->pipe_fd[1]);
			}
		}
		if (a->k)
			free(a->k);
		exit(0);
	}
	if (a->i == 0)
		a->k = ft_strjoin(l->line, "\n");
	else if (a->k)
	{
		a->tmp = a->k;
		a->k = ft_strjoin(a->tmp, l->line);
		free(a->tmp);
		a->tmp = a->k;
		a->k = ft_strjoin(a->tmp, "\n");
		free(a->tmp);
	}
}

void	child_heredoc(t_herdc *a, t_varint *l, char **evir)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	a->i = 0;
	l->env = 0;
	l->env = get_env(l->env, evir);
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

int	handle_heredoc(t_herdc *a, t_varint *l, char **evir)
{
	if (a->pid[a->j] < 0)
	{
		printf("Minishel: error fork\n");
		return (-1);
	}
	if (a->pid[a->j] == 0)
		child_heredoc(a, l, evir);
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

int	heredoc(t_commandes **c, t_varint *l, char *list, char **evir)
{
	t_herdc	a;

	init_hered_var(&a, c, l, list);
	while (list[a.o])
	{
		if (list[a.o] == '8' && list[a.o + 1] && list[a.o + 1] == '8')
		{
			if (l->tmp->files[l->x]
				&& !ft_strcmp(a.in_file, l->tmp->files[l->x]))
			{
				a.m = pipe(l->pipe_fd);
				if (a.m < 0)
					exit(EXIT_FAILURE);
				l->fd_rdc[l->nb_h] = l->pipe_fd[0];
			}
			a.pid[a.j] = fork();
			if (handle_heredoc(&a, l, evir) == (-1))
				return (-1);
		}
		else
			a.o++;
	}
	return (0);
}
