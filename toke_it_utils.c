/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_it_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:11:20 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 18:05:37 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dqbp(t_tokenz *m, char *str)
{
	int	tmp;

	tmp = 0;
	tmp = quote_bfr_pipe(str, m->i, '"');
	m->i++;
	m->j++;
	while (m->i < tmp)
	{
		m->array[m->j] = '1';
		if (str[m->i] == '"')
			m->array[m->j] = '3';
		else if (str[m->i] == '$')
			m->array[m->j] = '-';
		else if (str[m->i] == '\'')
			m->array[m->j] = '0';
		m->i++;
		m->j++;
	}
	if (str[m->i] == '"')
		m->array[m->j] = '3';
	else
		m->array[m->j] = '0';
}

void	sqbp(t_tokenz *m, char *str)
{
	int	tmp;

	tmp = 0;
	tmp = quote_bfr_pipe(str, m->i, '\'');
	m->i++;
	m->j++;
	while (m->i < tmp)
	{
		m->array[m->j] = '1';
		if (str[m->i] == '\'')
			m->array[m->j] = '0';
		else if (str[m->i] == '$')
			m->array[m->j] = '-';
		else if (str[m->i] == '"')
			m->array[m->j] = '0';
		m->i++;
		m->j++;
	}
	if (str[m->i] == '\'')
		m->array[m->j] = '0';
	else
		m->array[m->j] = '1';
}

void	xdfill_it(t_tokenz *m, char *str)
{
	if (str[m->i] == '"')
	{
		m->array[m->j] = '3';
		m->count++;
	}
	else if (str[m->i] == ' ' && m->count % 2 == 0)
		m->array[m->j] = '2';
	else if (str[m->i] == '$')
		m->array[m->j] = '-';
	else if (str[m->i] == '|' && m->count % 2 == 0)
		m->array[m->j] = '6';
	else
		m->array[m->j] = '1';
	m->j++;
	m->i++;
}

void	xsfill_it(t_tokenz *m, char *str)
{
	if (str[m->i] == '\'')
	{
		m->array[m->j] = '0';
		m->count++;
	}
	else if (str[m->i] == ' ' && m->count % 2 == 0)
		m->array[m->j] = '2';
	else if (str[m->i] == '$')
		m->array[m->j] = '-';
	else if (str[m->i] == '|' && m->count % 2 == 0)
		m->array[m->j] = '6';
	else
		m->array[m->j] = '1';
	m->j++;
	m->i++;
}

void	xdqbp(t_tokenz *m, char *str)
{
	m->i++;
	m->j++;
	m->count++;
	while (m->i < find_quotes_pair(str, '"'))
		xdfill_it(m, str);
	if (str[m->i] == '"')
		m->array[m->j] = '3';
	else
		lerreurat(3);
}
