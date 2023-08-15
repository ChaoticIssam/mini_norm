/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 01:13:05 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/13 04:15:22 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_over_flow(int in)
{
	if (in < 0 || in < 255)
	{
		while (in < 0)
			in += 256;
	}
	if (in > 0 && in > 255)
	{
		while (in > 255 && in > 0)
			in = in - 256;
	}
	return (in);
}

int	loop_through_int(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[0] == '-')
			i++;
		if (!ft_isdigit(s[i]))
		{
			write(2, "minishell: exit: dsgfd: numeric argument required\n", 51);
			return (0);
		}
		i++;
	}
	return (1);
}

void	t_exit(char **c)
{
	char	**s;

	s = c;
	if (!c[1])
		exit(0);
	if (s[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return ;
	}
	if (!loop_through_int(s[1]))
		return ;
	if (s[1])
		exit(check_for_over_flow(ft_atoi(s[1])));
	else
		exit(1);
}
