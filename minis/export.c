/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:28:00 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/13 07:48:10 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_input_to_export(t_envar **env, char **input, t_expo *l)
{
	l->i = 0;
	while (input[l->l][l->i])
	{
		if (l->k == 0 && input[l->l][l->i] == '+' &&
			input[l->l][l->i + 1] && input[l->l][l->i + 1] == '=')
		{
			fir_case(env, input, l);
			if (l->pr == NULL)
			{
				l->a = 1;
				l->ne = ft_ls_tnew(ft_str_rmc(input[l->l]));
				if (l->ne != NULL)
				{	
					ft_ls_tadd_back(env, l->ne);
					l->exist = 1;
				}
				l->k = 1;
				break ;
			}
		}
		else if (input[l->l][l->i] == '=' &&
			input[l->l][l->i - 1] != '+')
			second_case(env, input, l);
		l->i++;
	}
}

void	check_input_correct(t_envar **env, char **input, t_expo *l)
{
	if (check_ifinput_true(input[l->l]) == -1)
	{
		printf("minishell: export: %s: not a valid identifier\n",
			input[l->l]);
		l->a = 0;
	}
	l->pr = *env;
	while (l->pr)
	{
		if (!ft_str_ncmp(input[l->l], l->pr->value,
				ft_strlen(input[l->l])))
		{
			printf("breaak elm3lm\n");
			l->a = 0;
			break ;
		}
		l->pr = l->pr->next;
	}
	if (l->a)
		check_input_to_export(env, input, l);
	third_case(env, input, l);
}

void	t_export(t_envar **env, char **input)
{
	t_expo	l;

	l.k = 0;
	l.pr = *env;
	l.exist = 0;
	if (*input == NULL)
	{
		display_env_if_null(env);
		g_g.exit_status = 0;
	}
	else
	{
		l.l = 0;
		while (input[l.l])
		{
			l.a = 1;
			check_input_correct(env, input, &l);
			if (l.a == 0)
			{
				l.l++;
				continue ;
			}
			l.l++;
		}
	}
}
