/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:13:12 by iszitoun          #+#    #+#             */
/*   Updated: 2023/07/26 17:03:18 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isredi(char c)
{
	if (c == '9' || c == '8' || c == '4' || c == '5' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isprintbl(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int	ft_issospecial(char c)
{
	if (c == '\'' || c == '"' || c == '\\' || c == '/' || c == '`' || c == '#'
		|| c == '*' || c == '|')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_isspecial(char c)
{
	return (c == '6' || c == '4' || c == '3');
}
