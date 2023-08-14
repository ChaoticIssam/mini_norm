/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:04:58 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 08:50:14 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_q(char *list, t_count *c, char q, int i)
{
	if (q == '3')
		i = sec_q_rex(list, sec_q(list)) + 1;
	else if (q == '0')
		i = sec_q_rex(list, sec_s_q(list)) + 1;
	c->count++;
	return (i);
}

void	count_it(char *list, t_count *c, int i)
{
	if (list[i] == '3')
		i = for_q(list, c, list[i], i);
	if (i <= ft_strlen(list) && list[i] == '0')
		i = for_q(list, c, list[i], i);
	if (i <= ft_strlen(list) && list[i] == '1' && (list[i + 1] == '2' || !list[i
				+ 1]) && list[i] != '6')
		c->count++;
	if (i <= ft_strlen(list) && list[i] == '1' && list[i + 1] >= 52)
		c->count++;
}

void	init_count_vars(char *list, t_count *c)
{
	c->count = 0;
	c->len = ft_strlen(list);
}

char	*fill_var(t_commandes *tmp, envar *env, int i, int j)
{
	char	*var;
	int		x;
	int		env_len;

	env_len = ft_strlen(env->value);
	var = my_malloc(sizeof(char) * env_len + 1);
	x = 0;
	j++;
	while (tmp->commande[i][j] && tmp->commande[i][j] != ' ')
	{
		var[x] = tmp->commande[i][j];
		j++;
		x++;
	}
	var[x] = '\0';
	return (var);
}
