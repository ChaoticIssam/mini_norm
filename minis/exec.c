/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:05:18 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/14 01:33:13 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec1(t_envar **ev, char **input, int *fg)
{	
	if (!ft_str_ncmp("echo", input[0], 4))
	{
		t_echo(&input[1]);
		*fg = 1;
	}
	else if (!ft_str_ncmp("exit", input[0], 4))
	{
		t_exit(input);
		*fg = 1;
	}
	else if (!ft_str_ncmp("cd", input[0], 2))
	{
		t_cd(ev, input);
		*fg = 1;
	}
	else if (!ft_str_ncmp("pwd", input[0], 3))
	{
		t_pwd();
		*fg = 1;
	}
	return (*fg);
}

int	exec(t_envar **ev, char **input)
{
	int	fg;

	fg = 0;
	if (exec1(ev, input, &fg))
		return (fg);
	else if (!ft_str_ncmp("export", input[0], 6))
	{
		t_export(ev, &input[1]);
		fg = 1;
	}
	else if (!ft_str_ncmp("env", input[0], 3))
	{
		env(ev);
		fg = 1;
	}
	else if (!ft_str_ncmp("unset", input[0], 5))
	{
		unset(ev, &input[1]);
		fg = 1;
	}
	else
		return (0);
	return (fg);
}
