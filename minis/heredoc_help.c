/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:55:52 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 03:08:26 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_hered_var(t_herdc *a, t_commandes **c, t_varint *l, char *list)
{
	a->m = -1;
	a->k = NULL;
	a->pid = my_malloc (sizeof(int) * l->size);
	l->tmp = (*c);
	a->i = 0;
	l->x = 0;
	a->j = 0;
	a->o = 0;
	a->in_file = get_first_infile(l->tmp->files, list);
}

void	get_last_inf(char *list, int *flag, int *i, int *counter)
{
	if (list[*i] == '8' && list[*i + 1] && list[*i + 1] == '8')
	{
		*flag = 1;
		*i += 2;
	}
	else if (list[*i] == '4')
	{
		*flag = 0;
		*i++;
	}
	else if (list[*i] == '6' && *flag)
	{
		*counter++;
		*i++;
		*flag = 0;
	}
	else
		*i++;
}

int	count_last_inf_heredoc(char *list)
{
	int	i;
	int	flag;
	int	counter;

	counter = 0;
	flag = 0;
	i = 0;
	if (!list)
		return (0);
	while (list[i])
		get_last_inf(list, &flag, &i, &counter);
	if (flag)
		counter++;
	return (counter);
}

int	check_last_heredoc(char	*list)
{
	int	i;
	int	fg;

	if (!list)
		return (0);
	i = 0;
	fg = 0;
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			fg = 1;
			i += 2;
		}
		else if (list[i] == '4')
		{
			fg = 0;
			i++;
		}
		else
			i++;
	}
	return (fg);
}
