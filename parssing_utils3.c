/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:56:04 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 16:34:40 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	starting_parss(char *list, int i, int c)
{
	if (!list)
		return (0);
	if (list[i] == '6')
		i++;
	if (c > 0)
		i = c;
	while (list[i] == '2')
		i++;
	return (i);
}

void	start_stop(char *list, t_commande *s, int i)
{
	if (i + 1 <= ft_strlen(list) && ((list[i] != s->tmp) || list[i + 1] == '6'
			|| !list[i + 1]) && !ft_isredi(list[i]))
		get_end(s, i, list);
	if ((list[i] == '1') && list[i] != '3' && list[i] != '2' && s->lock
		&& list[i + 1] && !ft_isredi(list[i]))
		get_start(s, i, list);
	if (i != 0 && i + 1 <= ft_strlen(list) && list[i] == '1' && list[i
			- 1] == '2' && !list[i + 1] && !ft_isredi(list[i]))
		s->start = i;
}

int	for_quotes(char *list, t_commande *s, char *str, int i)
{
	s->j = i;
	s->commande[s->x] = quotes_quotes(str, list, i);
	if (quote_bfr_pipe(str, i, list[i]))
		i = quote_bfr_pipe(str, i, list[i]) + 1;
	else if (!quote_bfr_pipe(str, i, list[i]))
		i = s->j;
	if (list[i] == '3')
		i = sec_q_rex(list, i);
	else if (list[i] == '0')
		i = sec_q_rex(list, i);
	s->start = i + 1;
	s->x++;
	return (s->start);
}

void	rest_of_parss(char *list, char *str, t_commande *s, int i)
{
	if (!list)
		return ;
	if (list[i] && !s->lock1 && list[i] != '3' && str[s->start] != '"'
		&& str[s->start] != '\'' && str[s->start] != ' ' && s->end >= s->start
		&& !ft_isredi(list[i]))
		get_commande(s, str);
	if (list[i] == '2' && list[i + 1] == '2' && !ft_isredi(list[i]))
		skip_sp(s, list, i);
}

int	count_ptr(char *list, int bool)
{
	static int	i;
	static int	j;
	t_count		*c;

	if (!list)
		return (0);
	c = my_malloc(sizeof(t_count));
	i = initcount(bool, j);
	init_count_vars(list, c);
	while (list[i] && list[i] == '2')
		i++;
	while (i <= c->len && i >= 0 && list[i])
	{
		count_it(list, c, i);
		if (list[i] == '6')
		{
			i++;
			if (bool == 1)
				j = i;
			return (c->count);
		}
		i++;
	}
	return (c->count);
}
