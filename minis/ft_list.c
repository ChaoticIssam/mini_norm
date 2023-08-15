/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 05:23:13 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/14 03:09:02 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envar	*ft_ls_tnew(char *content)
{
	t_envar	*p;

	p = (t_envar *)malloc(sizeof(t_envar));
	if (!p)
		return (NULL);
	p->value = content;
	p->next = NULL;
	return (p);
}

void	ft_ls_tadd_back(t_envar **lst, t_envar *ne)
{
	t_envar	*ptr;

	ptr = *lst;
	if (ne && lst)
	{
		if (*lst == NULL)
		{
			*lst = ne;
		}
		else
		{
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = ne;
		}
	}
}

int	ft_lstsize(t_envar *lst)
{
	int		i;
	t_envar	*ptr;

	ptr = lst;
	i = 0;
	if (!lst)
		return (0);
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
int	ft_lst_size(t_commandes *lst)
{
	int			i;
	t_commandes	*ptr;

	if (!(lst))
		return (0);
	ptr = lst;
	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	ft_lstdelone(t_envar *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->value);
		free(lst);
	}
}
