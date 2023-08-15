/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:27 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/13 08:01:55 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_cases_to_unset(t_envar **head, t_uns *s, char **input)
{
	if (ft_str_ncmp(s->current->value, input[s->i],
		ft_strlen(input[s->i])) == 0)
	{
		*head = s->current->next;
		free(s->current->value);
		free(s->current);
		return ;
	}
	while (s->current != NULL
		&& ft_str_ncmp(input[s->i], s->current->value,
			ft_strlen(input[s->i])) != 0)
	{
		s->prev = s->current;
		s->current = s->current->next;
	}
	if (s->current == NULL)
	{
		printf("%s is not set.\n", input[s->i]);
	}
	else
	{	
		s->prev->next = s->current->next;
		free(s->current->value);
		free(s->current);
	}
}

void	unset(t_envar **head, char **input)
{
	t_uns	s;

	s.i = 0;
	if (*head == NULL)
	{
		printf("No environment variables to unset.\n");
		return ;
	}
	while (input[s.i])
	{
		s.current = *head;
		s.prev = NULL;
		check_cases_to_unset(head, &s, input);
			s.i++;
	}
}
