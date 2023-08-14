/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:22:51 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/12 23:53:27 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	t_pwd(void)
{
	char	current_dir[100];

	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
		printf("%s\n", current_dir);
	else
		printf("Error: Failed to get current directory\n");
}
