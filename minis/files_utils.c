/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:54:37 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 05:23:32 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ofiles(char *list, int *i, int *j)
{
	int	f;

	f = 0;
	if (list[*i] == '9' && list[*i + 1] && list[*i + 1] == '9')
	{
		*j += 1;
		*i += 2;
		f = 1;
	}
	else if (list[*i] == '5')
	{
		*j += 1;
		*i += 1;
		f = 1;
	}
	return (f);
}

int	check_ofiles(char *list, int *i, int *j)
{
	if (list[*i] == '8' && list[*i + 1] && list[*i + 1] == '8')
	{
		j++;
		if (in_file)
			free(in_file);
		printf("file j %s \n", files[*j]);
		in_file = ft_strdup(files[*j]);
		*i += 2;
	}
	else if (list[i] == '4')
	{
		j++;
		if (in_file)
			free(in_file);
		in_file = ft_strdup(files[j]);
		i++;
	}
}
char	*get_first_infile(char **files, char *list)
{
	int		i;
	int		j;
	char	*in_file;

	in_file = NULL;
	j = -1;
	i = 0;
	while (list[i])
	{
		if (!check_ofiles(list, &i, &j))
			;
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			j++;
			if (in_file)
				free(in_file);
			printf("file j %s \n", files[j]);
			in_file = ft_strdup(files[j]);
			i += 2;
		}
		else if (list[i] == '4')
		{
			j++;
			if (in_file)
				free(in_file);
			in_file = ft_strdup(files[j]);
			i++;
		}
		else
			i++;
	}
	return (in_file);
}

char	*get_first_outfile(char **files, char *list)
{
	int		i;
	int		j;
	char	*out_file;

	out_file = NULL;
	j = -1;
	i = 0;
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			j++;
			i += 2;
		}
		else if (list[i] == '4')
		{
			j++;
			i++;
		}
		if (list[i] == '9' && list[i + 1] && list[i + 1] == '9')
		{
			j++;
			if (out_file)
				free(out_file);
			out_file = ft_strdup(files[j]);
			i += 2;
		}
		else if (list[i] == '5')
		{
			j++;
			if (out_file)
				free(out_file);
			out_file = ft_strdup(files[j]);
			i++;
		}
		else
			i++;
	}
	return (out_file);
}
