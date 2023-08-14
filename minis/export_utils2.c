/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 07:48:13 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 02:56:04 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_env_if_null(t_envar **env)
{
	t_envar	*pr;
	char	*s;

	pr = *env;
	while (pr)
	{
		s = ft_strjoin("declare -x ", add_quots(pr->value));
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		pr = pr->next;
		free(s);
	}
	return ;
}

void	second_case(t_envar **env, char **input, t_expo *l)
{
	l->j = 0;
	while (input[l->l][l->j] && input[l->l][l->j] != '=')
		l->j++;
	l->pr = *env;
	while (l->pr)
	{
		if (!ft_str_ncmp(l->pr->value, input[l->l], l->j))
		{
			free(l->pr->value);
			l->pr->value = ft_strdup(input[l->l]);
			l->exist = 1;
			break ;
		}
		l->pr = l->pr->next;
	}
}

void	third_case(t_envar **env, char **input, t_expo *l)
{
	if (l->a == 1 && !l->exist)
	{
		l->ne = ft_ls_tnew(ft_strdup(input[l->l]));
		if (l->ne != NULL)
		{
			printf("add node\n");
			ft_ls_tadd_back(env, l->ne);
		}
	}
}
