/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parssing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:25:02 by iszitoun          #+#    #+#             */
/*   Updated: 2023/07/26 20:21:59 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote_parss(t_quote *q)
{
	q->i = 0;
	q->j = 0;
	q->last = 0;
	q->lock = 0;
	q->numoq = 0;
}

void	init_dq_parss(char *tknz, t_quote *q, int start)
{
	q->i = frst_q_rex(tknz, start);
	q->last = sec_q_rex(tknz, sec_q(tknz)) + 1;
	q->numoq = num_of_q(tknz, start);
}

void	init_sq_parss(char *tknz, t_quote *q, int start)
{
	q->i = frst_q_rex(tknz, start);
	q->last = sec_q_rex(tknz, sec_s_q(tknz)) + 1;
	q->numoq = num_of_s_q(tknz, start);
}

void	parss_quotes(char *str, char *tknz, t_quote *q, char token)
{
	if (token == '3')
		q->ptr[q->j] = '"';
	else if (token == '0')
		q->ptr[q->j] = '\'';
	q->j++;
	while (tknz[q->i] != '2' && tknz[q->i])
	{
		while (tknz[q->i] == token && tknz[q->i])
			q->i++;
		q->ptr[q->j] = str[q->i];
		q->j++;
		q->i++;
	}
	q->lock = 1;
}

void	fill_between_q(char *str, t_quote *q)
{
	q->ptr[q->j] = str[q->i];
	q->i++;
	q->j++;
}
