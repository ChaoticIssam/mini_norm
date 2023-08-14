/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:55:29 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/13 03:23:43 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	s = (char *)malloc(ft_strlen(s1) + 1);
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strcat(char *src, char *dst)
{
	char	*buff;
	int		i;
	int		ld;
	int		ls;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	buff = malloc (ld + ls + 1);
	i = 0;
	while (dst[i] != '\0')
	{
		buff[i] = dst[i];
		i++;
	}
	ld = i;
	i = 0;
	while (src[i] != '\0')
	{
		buff[ld + i] = src[i];
		i++;
	}
	buff[ld + i] = '\0';
	return (buff);
}

char	*ft_str_rmc(char *src)
{
	char	*buff;
	int		i;
	int		ls;
	int		j;

	ls = ft_strlen(src);
	buff = malloc (ls);
	i = 0;
	j = 0;
	printf("size of allocation %d\n", ls);
	printf ("src--->%s\n", src);
	while (src[i] != '\0')
	{
		if (src[i] != '+')
		{
			buff[j] = src[i];
			i++;
			j++;
		}
		else
			i++;
	}
	buff[j] = '\0';
	printf("buff---->%s\n", buff);
	return (buff);
}
