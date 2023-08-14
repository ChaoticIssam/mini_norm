/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils2_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 05:15:50 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:33:54 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_if_aro(t_commande *s, int i, char *list)
{
	list[i] = '1';
	i++;
	if (list[i] == '2')
		s->end = i;
	while (list[i] == '1' && list[i])
	{
		i++;
		if (list[i + 1] != '1')
			s->end = i;
	}
	return (s->end);
}

int	initcount(int bool, int j)
{
	if (bool == 1)
		j = 0;
	return (j);
}

int	is_pss(char c)
{
	if (ft_isprintbl(c) && !ft_issospecial(c) && !ft_isspace(c))
		return (1);
	return (0);
}

void	for_aro_tok(t_tokenz *m, char *str)
{
	m->array[m->j] = '@';
	plus_plus(m);
	while (str[m->i] && str[m->i] != ' ' && str[m->i] != '\t'
		&& str[m->i] != '"' && str[m->i] != '\'')
	{
		m->array[m->j] = '1';
		plus_plus(m);
	}
	if (str[m->i] == ' ' || str[m->i] == '\t' || str[m->i] == '\v'
		|| str[m->i] != '"' || str[m->i] != '\'')
		m->array[m->j] = '2';
}
