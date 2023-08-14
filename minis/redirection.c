/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:50:43 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 03:08:32 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_outfile(t_redirect *d, t_varint *l, char **files, char *list)
{
	if (list[l->d] == '4')
	{
		d->fd = open (files[l->x], O_RDWR);
		if (!ft_strcmp(files[l->x], d->in_file))
			l->in = d->fd;
		else
			close(d->fd);
		l->x++;
		return (1);
	}
	else if (list[l->d] == '5')
	{
		d->fd = open (files[l->x], O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (!ft_strcmp(files[l->x], d->out_file))
			l->out = d->fd;
		else
			close(d->fd);
		l->x++;
		return (1);
	}
	return (0);
}

int	heredoc_append(t_redirect *d, t_varint *l, char **files, char *list)
{
	if (list[l->d] == '8' && list[l->d + 1] && list[l->d + 1] == '8')
	{
		if (!ft_strcmp(files[l->x], d->in_file))
		{
			l->in = l->fd_rdc[l->nb_h];
			l->nb_h++;
		}
		l->x++;
		l->d++;
		return (1);
	}
	else if (list[l->d] == '9' && list[l->d + 1] && list[l->d + 1] == '9')
	{
		d->fd = open (files[l->x], O_CREAT | O_WRONLY
				| O_APPEND | O_RDONLY, 0644);
		if (!ft_strcmp(files[l->x], d->out_file))
			l->out = d->fd;
		else
			close(d->fd);
		l->x++;
		l->d++;
		return (1);
	}
	return (0);
}

void	redirection(t_varint *l, char **files, char *list)
{
	t_redirect	d;

	init_redirection(&d, l, files, list);
	while (list[l->d])
	{
		if (files[l->x])
		{
			d.tmp = check_bill_her(files[l->x], l->s, l->env);
			if (!d.tmp)
			{
				printf("minishell: %s: ambiguous redirect\n", files[l->x]);
				return ;
			}
			if (!infile_outfile(&d, l, files, list))
				heredoc_append(&d, l, files, list);
		}
		l->d++;
	}
	return ;
}
