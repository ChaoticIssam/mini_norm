/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:53:33 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 01:54:10 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**free_things(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		strings[i] = NULL;
		i++;
	}
	free(strings);
	strings = NULL;
	return (strings);
}

char	**env_tab(t_envar **ev)
{
	int		i;
	int		size;
	char	**env;
	t_envar	*tmp;

	size = ft_lstsize(*ev);
	tmp = *ev;
	env = my_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (tmp)
	{
		env[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	**split_path(t_envar **ev)
{
	char	**split;
	t_envar	*env;

	env = *ev;
	while (env && ft_str_ncmp(env->value, "PATH", 4))
		env = env->next;
	if (!env)
		return (NULL);
	split = ft_split(&env->value[5], ':');
	return (split);
}

char	*check_path(char **split, char *cmd)
{
	t_hop	va;

	va.arg = ft_split(cmd, ' ');
	va.i = 0;
	if (access(va.arg[0], X_OK) == 0)
		return (va.arg[0]);
	if (!split)
		return (NULL);
	va.p = ft_strjoin("/", va.arg[0]);
	va.arg = free_things(va.arg);
	while (split[va.i])
	{
		va.k = ft_strjoin(split[va.i], va.p);
		if (access(va.k, X_OK) == 0)
		{
			free(va.p);
			return (va.k);
		}
		free(va.k);
		va.i++;
	}
	free(va.p);
	return (NULL);
}

int	count_heredoc(char *list)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!list)
		return (0);
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{	
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}
