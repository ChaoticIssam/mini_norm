/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:37 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/13 05:45:28 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_line(t_main *main)
{
	printf("\033[0;31m");
	main->line = readline("Minishell$ ");
	printf("read_line ->%s\n", main->line);
	printf("\033[0m");
	add_history(main->line);
	if (main->line == NULL || !ft_strncmp(main->line, "exit"))
		exit(0);
	if (main->line)
	{
		main->m = my_malloc(sizeof(t_commandes));
		main->tmp = main->m;
		main->list = toknz_list(main->line, 0, 0);
	}
	printf("list ->%s\n", main->list);
}

void	print_before_pipe(t_main *main)
{
	while (main->tmp->commande[main->j])
	{
		ft_putstr(main->tmp->commande[main->j]);
		printf("<-commandes before pipe\n");
		main->j++;
	}
	while (main->tmp->files[main->x])
	{
		ft_putstr(main->tmp->files[main->x]);
		printf("<-files before pipe\n");
		main->x++;
	}
}

void	print_after_pipe(t_main *main)
{
	while (main->tmp->commande[main->j])
	{
		ft_putstr(main->tmp->commande[main->j]);
		printf("<-commande after pipe\n");
		main->j++;
	}
	while (main->tmp->files[main->x])
	{
		ft_putstr(main->tmp->files[main->x]);
		printf("<-files after pipe\n");
		main->x++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_main	*main;
	envar	*ev;

	(void)ac;
	(void)av;
	ev = 0;
	ev = get_env(ev, env);
	main = my_malloc(sizeof(t_main));
	int_main(main);
	while (1)
	{
		tcgetattr(0, &main->term);
		int_sig_main(main);
		signal(SIGINT, siginthandler);
		ft_read_line(main);
		if (*return_commande(main->list, main->line, 1, 0)
			|| *return_file(main->list, main->line, 1, main->tmp))
			int_main_before(main, ev);
		do_after_pipe(main, ev);
		multiple_pipe(&main->m, &ev, main->list);
		if (main->line)
			free(main->line);
		re_vars(main);
	}
}
