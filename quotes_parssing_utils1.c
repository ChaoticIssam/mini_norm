/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parssing_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:23:26 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/03 10:25:41 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quotes_full(char *tknz, t_quote *q, int start)
{
	if (tknz[start] == '3')
		init_dq_parss(tknz, q, start);
	else if (tknz[start] == '0')
		init_sq_parss(tknz, q, start);
	q->ptr = my_malloc(sizeof(char) * q->last - start - 1);
	q->j = 0;
}

char	*add_return_quote(t_quote *q)
{
	q->ptr[q->j] = '\0';
	return (q->ptr);
}
