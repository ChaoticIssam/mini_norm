/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:13:15 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/11 01:31:53 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redi(char *list, int bool)
{
	static int	i;
	static int	j;
	int			count;

	if (bool == 1)
		i = 0;
	if (bool == 0)
		i = j;
	count = 0;
	while (list[i] && list[i] == '2')
		i++;
	while (list[i])
	{
		if (ft_isredi(list[i]))
			count++;
		else if (list[i] == '6')
		{
			i++;
			if (bool == 1)
				j = i;
			return (count);
		}
		i++;
	}
	return (count);
}

int	count_pipe(char *list)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!list)
		return (0);
	check_pipe(list);
	while (list[i])
	{
		if (list[i] == '6')
			count++;
		i++;
	}
	return (count);
}

int	check_pipe(char *list)
{
	int	i;

	i = ft_strlen(list) - 1;
	if (i >= 0)
	{
		if (list[i] == '6')
			lerreurat(6);
		while (list[i] == '2')
			i--;
		if (list[i] == '6')
			lerreurat(6);
	}
	return (1);
}

int	quote_bfr_pipe(char *str, int i, char q)
{
	int	count;

	count = 0;
	while (str[i] != '|' && str[i])
	{
		if (str[i] == q)
			count++;
		if (count % 2 == 0 && (str[i + 1] == '|' || !str[i + 1]) && str[i] == q)
		{
			while (str[i] && i > 0 && (str[i] == ' ' || str[i] == '\t'))
				i--;
			return (i);
		}
		i++;
	}
	return (0);
}
