/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipes2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:58:26 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 03:46:45 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_process_in_pipe(t_exeec *z)
{
	g_g.child = 1;
	if (z->i > 0)
		close(z->old_ifd);
	z->old_ifd = z->pipe_fd[0];
	close(z->pipe_fd[1]);
	z->cmd = z->cmd->next;
	z->l->k++;
	if (check_last_heredoc(z->list_sp[z->l->k]))
		z->l->nb_h++;
	z->i++;
}

void	wait_child_and_signals(t_exeec *z)
{
	z->i = 0;
	while (z->i < z->s)
		waitpid(z->pid_fd[z->i++], &(z->child_status), 0);
	g_g.child = 1;
	if (WIFEXITED(z->child_status))
		g_g.exit_status = WEXITSTATUS(z->child_status);
	else if (WIFSIGNALED(z->child_status))
		g_g.exit_status = 128 + WTERMSIG(z->child_status);
	if (z->s > 1)
	{
		close(z->old_ifd);
		close(z->pipe_fd[0]);
		close(z->pipe_fd[1]);
	}
}

void	exec_command_in_pipe(t_envar **ev, t_exeec *z)
{
	if (z->cmd->commande[0])
	{
		if (exec(ev, z->cmd->commande))
			exit(g_g.exit_status);
		z->path_ex = split_path(ev);
		z->cp = check_path(z->path_ex, z->cmd->commande[0]);
		if (!z->cp)
		{
			write(2, "command not found\n", 18);
			g_g.exit_status = 1;
			exit(1);
		}
		execve(z->cp, z->cmd->commande, env_tab(ev));
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	child_process_in_pipe(t_exeec *z, t_envar **ev)
{
	signal(SIGINT, SIG_DFL);
	if (z->cmd->files && z->list_sp[z->l->k])
		redirection(z->l, z->cmd->files, z->list_sp[z->l->k]);
	if (z->i == 0)
		redirection_for_first_command(z);
	if (z->i == z->s - 1)
		redirection_for_last_command(z);
	else if (z->i > 0)
		redirection_for_midle_command(z);
	if (z->cmd->commande[0])
		exec_command_in_pipe(ev, z);
	exit(0);
}
