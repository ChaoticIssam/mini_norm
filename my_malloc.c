/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:12:58 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:38:08 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mal	*head(void)
{
	static t_mal	curr;

	if (curr.ptr == NULL)
	{
		curr.len = 10;
		curr.ptr = malloc(curr.len * sizeof(uintptr_t));
	}
	return (&curr);
}

int	get_available_pos(void)
{
	t_mal	*curr;
	int		pos;

	pos = 0;
	curr = head();
	while (pos < curr->pos)
	{
		if (curr->ptr[pos] == 0)
			break ;
		pos++;
	}
	return (pos);
}

void	*my_malloc(size_t size)
{
	t_mal		*curr;
	void		*new;
	uintptr_t	*ptr;
	int			pos;

	new = malloc(size);
	ft_memset(new, 0, size);
	pos = get_available_pos();
	curr = head();
	curr->ptr[pos] = (uintptr_t) new;
	if (pos == curr->pos)
		curr->pos++;
	if (curr->pos + 2 >= curr->len)
	{
		ptr = malloc(curr->len * 2 * sizeof(uintptr_t));
		ft_memcpy(ptr, curr->ptr, curr->len * sizeof(uintptr_t));
		free(curr->ptr);
		curr->ptr = ptr;
		curr->len *= 2;
	}
	return (new);
}
