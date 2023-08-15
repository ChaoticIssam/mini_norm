/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:37 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 01:20:12 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"

void	ft_read_line(t_main *main)
{
	printf("\033[0;31m");
	g_g.readline = 1;
	main->line = readline("Minishell$ ");
	g_g.readline = 0;
	printf("\033[0m");
	tcsetattr(0, TCSANOW, &main->term2);
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
	t_envar	*ev;

	(void)ac;
	(void)av;
	ev = 0;
	ev = get_env(ev, env);

	main = my_malloc(sizeof(t_main));
	int_main(main);
	signal_handler();
	while (1)
	{
		int_sig_main(main);
		ft_read_line(main);
		if (*main->list && *main->line && (*return_commande(main->list, main->line, 1, 0)
			|| *return_file(main->list, main->line, 1, main->tmp)))
		{
			int_main_before(main, ev);
			// print_before_pipe(main);
		}
		do_after_pipe(main, ev);
		multiple_pipe(&main->m, &ev, main->list, &main->senv, env);
		if (main->line)
			free(main->line);
		re_vars(main);
	}
}
