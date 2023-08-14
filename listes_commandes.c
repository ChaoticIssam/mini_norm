/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_commandes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:45:20 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/03 10:16:34 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commandes	*ft_lstnew(void *content)
{
	t_commandes	*first;

	first = my_malloc(sizeof(t_commandes));
	if (!first)
		return (NULL);
	first->commande = ft_split(content, ' ');
	first->next = NULL;
	return (first);
}

t_commandes	*ft_lstlast(t_commandes *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_commandes **lst, t_commandes *new)
{
	t_commandes	*newlst;

	newlst = *lst;
	if (*lst)
	{
		newlst = ft_lstlast(newlst);
		newlst->next = new;
	}
	else
		*lst = new;
}
