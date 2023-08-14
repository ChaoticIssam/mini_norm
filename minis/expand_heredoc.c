/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:47:21 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 02:36:44 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_bill_her(char *str, t_env *senv, t_envar *env)
{
	t_bill	*bill;

	bill = my_malloc(sizeof(t_bill));
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

char	*fill_var_her(char *str, t_envar *env, int i)
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

char	*fill_path_her(t_envar *env, t_env *s)
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
