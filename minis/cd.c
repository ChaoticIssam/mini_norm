/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:20:35 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/13 18:44:51 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_num_args(t_envar	**ev, t_tcd *l, char **input)
{
	l->i = 2;
	l->v = *ev;
	while (input[l->i])
	{
		if (input[l->i])
		{
			printf("Error: too many argument");
			break ;
		}
		l->i++;
	}
}

void	check_home_arg(t_envar	**ev, t_tcd *l, char **input)
{
	check_num_args(ev, l, input);
	printf("--->folder %s\n", input[1]);
	if (!input[1] || !ft_strcmp(input[1], "~"))
	{
		while (l->v)
		{
			if (!ft_str_ncmp(l->v->value, "HOME", 4))
				break ;
			l->v = l->v->next;
		}
		if (!l->v)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		input[1] = &(l->v->value[5]);
	}
}

void	get_pwd(t_envar	**ev, t_tcd *l)
{
	l->s = *ev;
	while (l->s)
	{
		if (!ft_str_ncmp(l->s->value, "PWD", 3))
		{
			l->wd = ft_strdup(&(l->s->value[4]));
			free(l->s->value);
			l->s->value = ft_strjoin("PWD=", l->current_dir);
		}
		l->s = l->s->next;
	}
	l->s = *ev;
	while (l->s)
	{
		if (!ft_str_ncmp(l->s->value, "OLDPWD", 6))
		{
			free(l->s->value);
			l->s->value = ft_strjoin("OLDPWD=", l->wd);
			break ;
		}
		l->s = l->s->next;
	}
	if (l->s == NULL)
		ft_ls_tadd_back(ev,
			ft_ls_tnew(ft_strjoin("OLDPWD=", l->wd)));
}

void	t_cd(t_envar **ev, char **input)
{
	t_tcd	l;

	check_home_arg(ev, &l, input);
	if (!ft_strcmp(input[1], "-"))
	{
		cd_old(ev, &l, input);
		if (l.s == NULL)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	else if (chdir(input[1]) != 0)
		printf("cd: %s: No such file or directory\n", input[1]);
	else
	{
		if (!getcwd(l.current_dir, sizeof(l.current_dir)))
		{
			return ;
		}
		cd_as(ev, &l);
		if (l.s == NULL)
			ft_ls_tadd_back(ev, ft_ls_tnew(ft_strjoin("OLDPWD=", l.wd)));
	}
}
