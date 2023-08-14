/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:52:43 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/03 10:15:36 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*ft_lstnew_files(void *content)
{
	t_files	*first;

	first = my_malloc(sizeof(t_files));
	if (!first)
		return (free(first), NULL);
	first->files = ft_split(content, ' ');
	first->next = NULL;
	return (first);
}

t_files	*ft_lstlast_files(t_files *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_files(t_files **lst, t_files *new)
{
	t_files	*newlst;

	newlst = *lst;
	if (*lst)
	{
		newlst = ft_lstlast_files(newlst);
		newlst->next = new;
	}
	else
		*lst = new;
}
