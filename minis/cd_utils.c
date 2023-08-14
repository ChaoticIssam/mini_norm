/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:45:49 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/13 16:48:25 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_old(t_envar	**ev, t_tcd *l, char **input)
{
	l->s = *ev;
	while (l->s)
	{
		if (!ft_str_ncmp(l->s->value, "OLDPWD", 6))
		{
			input[1] = &(l->s->value[7]);
			if (chdir(input[1]) != 0)
				printf("cd: %s: No such file or directory\n", input[1]);
			else
			{
				if (!getcwd(l->current_dir, sizeof(l->current_dir)))
					return ;
				else
				{
					get_pwd(ev, l);
				}
			}
			return ;
		}
		l->s = l->s->next;
	}
}

void	cd_as(t_envar	**ev, t_tcd *l)
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
}
