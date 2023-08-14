/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_her.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:21:19 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 05:28:30 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_bill_her(char *str, t_env *senv, envar *env)
{
	t_bill	*bill;

	bill = my_malloc(sizeof(t_bill));
	bill->i = 0;
	while (str[bill->i] && str[bill->i] != '\n')
	{
		if ((str[bill->i] == '"' || str[bill->i] == '\'')
			&& str[bill->i][bill->j + 1] == '$')
		{
			while (str[bill->i] && str[bill->i] != '\n')
			{
				str[bill->i] = str[bill->i + 1];
				bill->i++;
			}
		}
		if (str[0] == '$')
			done_normal_her(str, senv, env, bill);
		bill->i++;
	}
}

void	done_normal_her(char *str, t_env *senv, envar *env, t_bill *bill)
{
	senv->var = fill_var_her(str, env, bill->i);
	senv->path = fill_path_her(env, senv);
	if (senv->var[0] == '?')
	{
		free(tmp->commande[bill->i]);
		tmp->commande[bill->i] = ft_itoa(g_g.exit_status);
	}
	if (senv->path != NULL)
	{
		free(tmp->commande[bill->i]);
		tmp->commande[bill->i] = senv->path;
	}
	else
		return ;
}

char	*fill_var_her(char *str, envar *env, int i)
{
	char	*var;
	int		x;
	int		env_len;

	env_len = ft_strlen(env->value);
	var = my_malloc(sizeof(char) * env_len + 1);
	x = 0;
	i++;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
	{
		var[x] = str[i];
		i++;
		x++;
	}
	var[x] = '\0';
	return (var);
}

char	*fill_path_her(envar *env, t_env *s)
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
