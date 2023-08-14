/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 07:45:25 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 02:56:00 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quots(char *value)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (value[i] == '=')
	{
		i++;
		buff = malloc(i + 1);
		j = 0;
		while (j < i && value[j])
		{
			buff[j] = value[j];
			j++;
			if (value[j] != '=' && value[j - 1] == '=')
				break ;
		}
		buff[j] = '\0';
		return (ft_strjoin(ft_strjoin(ft_strjoin(buff, "\""), &value[i]), "\""));
	}
	else
		return (value);
}

int	check_ifinput_true(char *input)
{
	int		i;

	i = 1;
	if (!ft_isalpha(input[0]) && input[0] != '_')
		return (-1);
	while (input[i] && (ft_isalpha(input[i]) || ft_isdigit(input[i])
			|| input[i] == '_' || input[i] == '+'))
	{
		if (input[i] == '+')
		{
			if (input[i + 1] && input[i + 1] == '=')
				return (1);
			return (-1);
		}
		if (input[i] == '=')
			return (1);
		i++;
	}
	if (input[i] != '=' && input[i] != '\0')
		return (-1);
	return (1);
}

int	check_for_eq(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	join_strings(t_envar **env, char **input, t_expo *l)
{
	l->pr = *env;
	while (l->pr)
	{
		if (!ft_str_ncmp(l->pr->value, input[l->l], l->j))
		{
			printf("%d that are compared = %d\n",
				l->j, ft_str_ncmp(l->pr->value, input[l->l], l->j));
			if (!check_for_eq(l->pr->value))
			{
				l->tmp = l->pr->value;
				l->pr->value = ft_strjoin(l->pr->value, "=");
				free(l->tmp);
			}
			l->nv = ft_strcat(&(input[l->l][l->j + 2]), l->pr->value);
			printf("nv string concatenat %s\n", l->nv);
			free(l->pr->value);
			l->pr->value = l->nv;
			l->exist = 1;
			l->a = 1;
			l->k = 1;
			break ;
		}
		l->pr = l->pr->next;
	}
}

void	fir_case(t_envar **env, char **input, t_expo *l)
{
	l->j = 0;
	while (input[l->l][l->j] && input[l->l][l->j] != '+')
		l->j++;
	join_strings(env, input, l);
}
