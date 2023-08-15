/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:54:37 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 05:57:34 by mokhalil         ###   ########.fr       */
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

int	check_ifiles(char *list, t_filino *f, char **files)
{
	int	fs;

	fs = 0;
	if (list[f->i] == '8' && list[f->i + 1] && list[f->i + 1] == '8')
	{
		f->j++;
		if (f->in_file)
			free(f->in_file);
		f->in_file = ft_strdup(files[f->j]);
		f->i += 2;
		fs = 1;
	}
	else if (list[f->i] == '4')
	{
		f->j++;
		if (f->in_file)
			free(f->in_file);
		f->in_file = ft_strdup(files[f->j]);
		f->i++;
		fs = 1;
	}
	return (fs);
}

char	*get_first_infile(char **files, char *list)
{
	t_filino	f;

	f.in_file = NULL;
	f.j = -1;
	f.i = 0;
	while (list[f.i])
	{
		check_ofiles(list, &f.i, &f.j);
		if (!check_ifiles(list, &f, files))
			f.i++;
	}
	return (f.in_file);
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
