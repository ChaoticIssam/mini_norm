/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:36:42 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/11 03:05:54 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_file_parss(char *list, t_file *f, t_commandes *m, int bool)
{
	m->files = my_malloc(sizeof(char *) * count_redi(list, bool) + 2);
	f->fstart = 0;
	f->fend = 0;
	f->fx = 0;
	f->lock = 0;
}

int	skip_file_parss(char *list, int i)
{
	while (ft_isredi(list[i]))
		i++;
	while (list[i] == '2' || list[i] == '1')
		i++;
	return (i);
}

int	find_end_file_parss(char *list, t_file *f, int i)
{
	while (list[i] == '*')
	{
		if (list[i + 1] != '*' || !list[i + 1])
		{
			f->fend = i;
			f->lock = 1;
		}
		i++;
	}
	return (i);
}

void	fill_file_parss(char *str, t_commandes *m, t_file *f)
{
	if (f->lock && f->fend >= f->fstart)
	{
		m->files[f->fx] = ft_substr(str, f->fstart, f->fend - f->fstart + 1);
		f->fx++;
		f->lock = 0;
	}
}

int	first_file_parss(int bool, int i)
{
	if (bool == 1)
		return (0);
	return (i);
}
