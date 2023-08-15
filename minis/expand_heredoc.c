/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:47:21 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 06:52:36 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "readline.h"

char	*check_bill_her(char *str, t_env *senv, t_envar *env)
{
	t_bill	*bill;

	bill = my_malloc(sizeof(t_bill));
	senv = my_malloc(sizeof(t_env));
	bill->i = 0;
	if ((str[bill->i] == '"' || str[bill->i] == '\'')
		&& str[bill->i + 1] == '$')
	{
		while (str[bill->i] && str[bill->i] != '\n')
		{
			str[bill->i] = str[bill->i + 1];
			bill->i++;
		}
	}
	if (str[0] == '$')
	{
		done_normal_her(str, senv, env, bill);
		str = senv->path;
		return (str);
	}
	return (str);
}

void	done_normal_her(char *str, t_env *senv, t_envar *env, t_bill *bill)
{
	senv->var = my_malloc(sizeof(char) * 100);
	senv->path = my_malloc(sizeof(char) * 100);
	senv->var = fill_var_her(str, env, bill->i);
	senv->path = fill_path_her(env, senv);
	if (senv->var[0] == '?')
	{
		free(str);
		str = ft_itoa(g_g.exit_status);
	}
	if (senv->path != NULL)
		free(str);
	else
		return ;
}

char	*var_get_her(t_envar *env)
{
	int		j;
	char	*envv;

	j = 0;
	envv = malloc(sizeof(char) * 100);
	while (env->value[j])
	{
		if (env->value[j] == '=')
			return (envv);
		envv[j] = env->value[j];
		j++;
	}
	return (envv);
}

char	*fill_var_her(char *str, t_envar *env, int i)
{
	char	*var;
	int		x;
	(void)env;
	if (!str)
		return (NULL);
	var = my_malloc(sizeof(char) * 100);
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

char	*get_path_her(t_envar *env)
{
	int		j;
	int		x;
	char	*envr;

	envr = malloc(sizeof(char) * 100);
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


char	*fill_path_her(t_envar *env, t_env *s)
{
	char	*path;

	path = my_malloc(sizeof(char) * 100);
	while(env)
	{
		if (!ft_strncmp(s->var, var_get_her(env)))
		{
			path = get_path_her(env);
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}
