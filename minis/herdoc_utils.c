/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:29:56 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 05:33:33 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_hered_var(t_herdc *a, t_commandes **c, t_varint *l, char *list)
{
	a->m = -1;
	a->k = NULL;
	a->pid = my_malloc(sizeof(int) * l->size);
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
