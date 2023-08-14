/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:49:47 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 02:55:36 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_envar **ev)
{
	int		i;
	t_envar	*pr;

	pr = *ev;
	i = 0;
	while (pr)
	{
		if (strchr(pr->value, '='))
		{
			write(1, pr->value, ft_strlen(pr->value));
			write(1, "\n", 1);
		}
		pr = pr->next;
	}
}
