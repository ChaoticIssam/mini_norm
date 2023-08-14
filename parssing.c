/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:57 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 05:29:18 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_commande_var(t_commande *s, char *list, int bool)
{
	s->x = 0;
	s->start = 0;
	s->j = 0;
	s->end = 0;
	s->ptr_num = count_ptr(list, bool);
	s->commande = calloc(sizeof(char *), s->ptr_num + 2);
	s->lock = 0;
	s->lock1 = 1;
	s->tmp = 0;
}

char	**return_commande(char *list, char *str, int bool, int c)
{
	t_commande	*s;
	static int	i;

	s = my_malloc(sizeof(t_commande));
	int_commande_var(s, list, bool);
	if (bool == 1)
		i = -1;
	expand_erreur(list);
	i = starting_parss(list, ++i, c);
	while (i + 1 <= ft_strlen(list) && list[i] && s->x <= count_ptr(list, bool)
		&& list[i] != '6')
	{
		if (ft_isredi(list[i]))
		{
			while ((list[i] == '*' || list[i] == '2' || ft_isredi(list[i])))
				i++;
			if (list[i] == '6' || !list[i])
				return (s->commande);
		}
		if ((list[i] == '3' || list[i] == '0') && !ft_isredi(list[i]))
			i = for_quotes(list, s, str, i) - 1;
		start_stop(list, s, i);
		rest_of_parss(list, str, s, i++);
	}
	return (s->commande);
}

char	**return_file(char *list, char *str, int bool, t_commandes *tmp)
{
	static int	i;
	t_file		*f;

	f = my_malloc(sizeof(t_file));
	init_file_parss(list, f, tmp, bool);
	i = first_file_parss(bool, i);
	if (list[i] == '6')
		i++;
	while (list[i] == '2' || list[i] == '1')
		i++;
	while (i <= ft_strlen(list) && list[i] && list[i] != '6')
	{
		i = skip_file_parss(list, i);
		if (list[i] == '*')
			f->fstart = i;
		i = find_end_file_parss(list, f, i);
		fill_file_parss(str, tmp, f);
		i++;
	}
	if (i < ft_strlen(list))
		return_commande(list, str, bool, i);
	return (tmp->files);
}

char	*quotes_quotes(char *str, char *tknz, int start)
{
	t_quote	*q;

	q = my_malloc(sizeof(t_quote));
	init_quote_parss(q);
	init_quotes_full(tknz, q, start);
	while (q->i < q->last && q->numoq % 2 == 0)
	{
		if (tknz[q->i] == '0' || tknz[q->i] == '3')
			q->i++;
		if (tknz[q->i] == '-' && tknz[q->i + 1] == '3')
			parss_quotes(str, tknz, q, tknz[q->i + 1]);
		else if (tknz[q->i] == '-' && tknz[q->i + 1] == '0')
			parss_quotes(str, tknz, q, tknz[q->i + 1]);
		if (tknz[q->i] == '1' || tknz[q->i] == '-')
			fill_between_q(str, q);
		if (!tknz[q->i] || tknz[q->i] == '6' || ((tknz[q->i] == '3'
					|| tknz[q->i] == '0') && !tknz[q->i + 1]))
			return (q->ptr[q->j] = '\0', q->ptr);
	}
	if ((tknz[q->i] == '6' && q->i > q->last - 1) || (q->i == sec_q_rex(tknz,
				sec_q(tknz) + 2) && q->last > 0))
		q->ptr = add_return_quote(q);
	return (NULL);
}
