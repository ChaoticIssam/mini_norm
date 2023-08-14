/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:38:18 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:20:58 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_end(t_commande *s, int i, char *list)
{
	s->end = i - 1;
	if ((i + 1 <= ft_strlen(list) && !list[i + 1]))
		s->end = i;
	s->lock1 = 0;
	s->lock = 1;
	if (list[i] == '@' && list[i - 1] == '1')
		end_if_aro(s, i, list);
	else if (list[i] == '@' && list[i - 1] == '2')
		s->end = i;
	if (list[i] == '2')
		s->end = i - 1;
	if (i + 1 <= ft_strlen(list) && list[i + 1] == '6')
	{
		s->end = i;
		if (list[i] == '2')
			s->end = i - 1;
		s->lock = 0;
	}
}

void	get_start(t_commande *s, int i, char *list)
{
	s->start = i;
	s->lock = 0;
	s->lock1 = 1;
	s->tmp = list[i];
}

void	last_world_ig(t_commande *s, int i)
{
	s->start = i;
}

void	get_commande(t_commande *s, char *str)
{
	s->commande[s->x] = ft_substr(str, s->start, s->end - s->start + 1);
	s->x++;
}

void	skip_sp(t_commande *s, char *list, int i)
{
	while (list[i] == '2')
		i++;
	i--;
	s->start = i;
	s->lock1 = 0;
}
