/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 01:02:37 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/14 05:24:44 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_single_command(t_exeec *z, char *list)
{
	z->stin = dup(0);
	z->stout = dup(1);
	if (z->cmd->files)
	{
		if (heredoc(&(z->cmd), z->l, list) == -1)
		{
			close(z->l->pipe_fd[1]);
			return (0);
		}
		z->l->in = -1;
		z->l->out = -1;
		z->l->nb_h = 0;
		redirection(z->l, z->cmd->files, list);
	}
	return (1);
}

void	exec_command_in_single_child(t_exeec *z, t_envar **ev)
{
	close(z->l->pipe_fd[1]);
	if (z->cmd->commande[0])
	{
		signal(SIGINT, SIG_DFL);
		z->path_ex = split_path(ev);
		z->cp = check_path(z->path_ex, z->cmd->commande[0]);
		if (!z->cp)
		{
			write(2, "command not found\n", 18);
			exit(1);
		}
		execve(z->cp, z->cmd->commande, env_tab(ev));
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	parent_in_single_child(t_exeec *z)
{
	g_g.child = 1;
	waitpid(z->l->pid, &(z->child_status), 0);
	dup2(z->stout, 1);
	dup2(z->stin, 0);
	if (WIFEXITED(z->child_status))
		g_g.exit_status = WEXITSTATUS(z->child_status);
	else if (WIFSIGNALED(z->child_status))
		g_g.exit_status = 128 + WTERMSIG(z->child_status);
}

void	single_command(t_exeec *z, t_envar **ev)
{
	if (exec(ev, z->cmd->commande))
	{
		if (z->l->in != -1)
			close(z->l->in);
		if (z->l->out != -1)
			close(z->l->out);
		dup2(z->stout, 1);
		dup2(z->stin, 0);
		return ;
	}
	else
	{
		z->l->pid = fork();
		if (z->l->pid < 0)
		{
			printf("Minishel: error fork\n");
			return ;
		}
		else if (z->l->pid == 0)
			exec_command_in_single_child(z, ev);
		else
			parent_in_single_child(z);
		g_g.child = 0;
	}
}

void	single_node_exec(t_exeec *z, char *list, t_envar **ev)
{
	if (!heredoc_single_command(z, list))
		return ;
	if (z->l->in != -1)
	{
		dup2(z->l->in, 0);
		close(z->l->in);
	}
	if (z->l->out != -1)
	{
		dup2(z->l->out, 1);
		close(z->l->out);
	}
	if (z->cmd->commande)
		single_command(z, ev);
	return ;
}
