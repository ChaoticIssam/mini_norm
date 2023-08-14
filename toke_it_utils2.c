/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_it_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:57:46 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:37:55 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	plus_plus(t_tokenz *m)
{
	m->i++;
	m->j++;
}

void	starting(char *str, t_tokenz *m)
{
	if (ft_isspace(str[m->i]))
		m->array[m->j] = '2';
	else
		m->array[m->j] = '*';
}

void	check_and_fill(char *str, t_tokenz *m)
{
	while (!ft_isspace(str[m->i]) && ft_isprintbl(str[m->i])
		&& !ft_issospecial(str[m->i]) && str[m->i])
	{
		if (str[m->i] == '>' || str[m->i] == '<')
		{
			toknz_list(str, m->i, m->j);
			break ;
		}
		m->array[m->j] = '*';
		plus_plus(m);
	}
}

void	fill_in_single(char *str, t_tokenz *m)
{
	while (!ft_isspace(str[m->i]) && ft_isprintbl(str[m->i])
		&& !ft_issospecial(str[m->i]) && str[m->i])
	{
		if (str[m->i] == '>' || str[m->i] == '<')
		{
			toknz_list(str, m->i, m->j);
			break ;
		}
		m->array[m->j] = '*';
		plus_plus(m);
	}
}

void	fill_in_double(char *str, t_tokenz *m, char token)
{
	while (!ft_isspace(str[m->i]) && ft_isprintbl(str[m->i])
		&& !ft_issospecial(str[m->i]) && str[m->i])
	{
		if ((str[m->i] == '>' && str[m->i + 1] == '>') || (str[m->i] == '<'
				&& str[m->i + 1] == '<'))
		{
			m->array[m->j] = token;
			plus_plus(m);
			m->array[m->j] = token;
			plus_plus(m);
		}
		if (str[m->i] == '>' || str[m->i] == '<')
		{
			toknz_list(str, m->i, m->j);
			break ;
		}
		m->array[m->j] = '*';
		plus_plus(m);
	}
}
