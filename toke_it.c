/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 06:50:29 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:34:15 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_the_rest2(t_tokenz *m, char *str)
{
	if (str[m->i] == ' ' || str[m->i] == '\t' || str[m->i] == '\v')
		m->array[m->j] = '2';
	else if (str[m->i] == '"')
	{
		if (m->i - 1 >= 0 && str[m->i - 1] == '=')
			m->array[m->j - 1] = '@';
		dquotes_tokenz(m, str);
	}
	else if (str[m->i] == '\'')
	{
		if (str[m->i - 1] == '=')
			m->array[m->j - 1] = '@';
		squotes_tokenz(m, str);
	}
	else if (str[m->i] == '=' && str[m->i + 1] != ' ')
		for_aro_tok(m, str);
	else if (str[m->i])
		m->array[m->j] = '1';
}

void	fill_the_rest(t_tokenz *m, char *str)
{
	if (str[m->i] == '|')
		m->array[m->j] = '6';
	else if (str[m->i] == '>' && !(str[m->i + 1] == '>'))
	{
		redi_tokenz(m, str, '5');
		m->i--;
		m->j--;
	}
	else if (str[m->i] == '<' && !(str[m->i + 1] == '<'))
	{
		redi_tokenz(m, str, '4');
		m->i--;
		m->j--;
	}
	else
		fill_the_rest2(m, str);
}

void	var_def(t_tokenz *m, char *str, int i, int j)
{
	m->array = NULL;
	m->i = 0;
	m->j = 0;
	if (i > 0)
	{
		m->i = i;
		m->j = j;
	}
	m->j = 0;
	m->count = 0;
	m->array = my_malloc(sizeof(char) * ft_strlen(str) + 1);
}

char	*toknz_list(char *str, int i, int j)
{
	t_tokenz	*m;

	m = my_malloc(sizeof(t_tokenz));
	var_def(m, str, i, j);
	while (m->i <= ft_strlen(str) && str[m->i])
	{
		if (str[m->i] == '>' && str[m->i + 1] == '>')
			double_redi_tokenz(m, str, '9');
		else if (str[m->i] == '<' && str[m->i + 1] == '<')
			double_redi_tokenz(m, str, '8');
		fill_the_rest(m, str);
		m->i++;
		m->j++;
	}
	return (m->array);
}
