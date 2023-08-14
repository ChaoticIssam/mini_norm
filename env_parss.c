/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:18:51 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 18:46:26 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(t_commandes *m)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (m->commande[i] && m->commande[i][j])
	{
		if (m->commande[i][j] == '$')
		{
			j++;
			while (m->commande[i][j] && m->commande[i][j] != ' ')
			{
				count++;
				j++;
			}
			if (m->commande[i][j] == ' ' || !m->commande[i][j])
				return (count);
		}
		i++;
	}
	return (0);
}

char	*var_gett(envar *env)
{
	int		j;
	char	*envv;

	envv = my_malloc(sizeof(char) * 100);
	j = 0;
	while (env->value[j])
	{
		if (env->value[j] == '=')
			return (envv);
		envv[j] = env->value[j];
		j++;
	}
	return (0);
}

char	*get_path(envar *env)
{
	int		j;
	int		x;
	char	*envr;

	envr = my_malloc(sizeof(char) * 100);
	j = 0;
	x = 0;
	while (env->value[j])
	{
		if (env->value[j] == '=')
		{
			j++;
			while (env->value[j])
			{
				envr[x] = env->value[j];
				x++;
				j++;
			}
			if (!env->value[j])
				return (envr);
		}
		j++;
	}
	return (0);
}

char	*fill_path(envar *env, t_env *s)
{
	int		j;
	char	*path;

	j = 0;
	path = my_malloc(sizeof(char) * 100);
	while (env->value[j] && env->value[j] != '=')
		j++;
	j++;
	while (env->next)
	{
		if (!ft_strncmp(s->var, var_gett(env)))
		{
			path = get_path(env);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}
