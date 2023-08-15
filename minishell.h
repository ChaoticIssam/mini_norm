/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:49 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 06:25:52 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline.h"
# include "history.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdint.h>

typedef struct redirect
{
	int		i;
	int		fd;
	char	*in_file;
	char	*out_file;
	char	*tmp;
}	t_redirect;

typedef struct s_heredoc
{
	int		i;
	int		*pid;
	int		j;
	char	*k;
	int		o;
	char	*tmp;
	char	*in_file;
	int		m;
	int		heredoc_status;
}	t_herdc;
typedef struct EnvVar
{
	char				*value;
	struct EnvVar		*next;
}						t_envar;

typedef struct global
{
	int					exit_status;
	int					readline;
	int					child;
	int					echo;
}						t_global;

extern t_global			g_g;

typedef struct s_mal
{
	int					pos;
	uintptr_t			*ptr;
	int					len;
}						t_mal;

typedef struct s_node
{
	int					token;
	struct s_node		*next;
}						t_node;

typedef struct s_tokenz
{
	int					i;
	int					j;
	int					count;
	char				*array;
}						t_tokenz;

typedef struct s_commande
{
	char				**commande;
	int					j;
	int					x;
	int					start;
	int					end;
	int					ptr_num;
	int					lock;
	int					lock1;
	int					tmp;
}						t_commande;

typedef struct s_file
{
	int					fstart;
	int					fend;
	int					fx;
	int					lock;
}						t_file;

typedef struct s_commandes
{
	char				**commande;
	char				**files;
	struct s_commandes	*next;
}						t_commandes;

typedef struct s_files
{
	char				**files;
	struct s_files		*next;
}						t_files;

typedef struct s_quote
{
	int					i;
	int					j;
	int					lock;
	int					last;
	char				*ptr;
	int					numoq;
}						t_quote;

typedef struct s_env
{
	char				*var;
	char				*path;
	t_envar				*env_export;
	struct s_env		*next;
}						t_env;

typedef struct s_bill
{
	int					i;
	int					j;
}						t_bill;

typedef struct s_count
{
	int					count;
	int					len;
}						t_count;

typedef struct s_main
{
	char				*line;
	char				*list;
	t_commandes			*m;
	t_commandes			*tmp;
	t_files				*f;
	t_files				*tmp1;
	t_env				*senv;
	int					i;
	int					j;
	int					x;
	struct termios		term;
	struct termios		term2;
}						t_main;
typedef struct s_hip
{
	int		i;
	char	*p;
	char	*k;
	char	**arg;
}	t_hop;

typedef struct s_varint
{
	int			in;
	int			out;
	int			fd;
	int			k;
	int			d;
	int			x;
	int			size;
	t_commandes	*tmp;
	char		*line;
	int			*fd_rdc;
	int			nb_h;
	int			pipe_fd[2];
	int			pid;
	t_env		*s;
	t_envar		*env;
}				t_varint;

typedef struct s_expo
{
	t_envar	*ne;
	t_envar	*pr;
	char	*s;
	char	*nv;
	int		i;
	int		j;
	int		l;
	int		a;
	int		exist;
	int		k;
	char	*tmp;
}			t_expo;

typedef struct s_cd
{
	t_envar	*v;
	t_envar	*s;
	char	*wd;
	char	current_dir[100];
	int		i;
}		t_tcd;

typedef struct s_unset
{
	t_envar	*current;
	t_envar	*prev;
	int		i;
}	t_uns;

typedef struct s_exec
{
	t_commandes	*cmd;
	t_varint	*l;
	char		**path_ex;
	char		**list_sp;
	int			pipe_fd[2];
	int			*pid_fd;
	char		*cp;
	int			s;
	int			i;
	int			old_ifd;
	int			m;
	int			child_status;
	int			t;
	int			stout;
	int			stin;
}				t_exeec ;

typedef struct  g_fils
{
	int		i;
	int		j;
	char	*in_file;
}			t_filino;

char					*get_first_infile(char **files, char *list);
char					*get_first_outfile(char **files, char *list);
int						count_heredoc(char *list);
int						count_last_inf_heredoc(char *list);
void					wait_child_and_signals(t_exeec *z);
int						check_last_heredoc(char	*list);
int						heredoc_in_multiple_pipe(t_commandes **c, char *list, t_exeec *z, char **evir);
void					redirection_for_first_command(t_exeec *z);
void					redirection_for_midle_command(t_exeec *z);
void					redirection_for_last_command(t_exeec *z);
void					exec_command_in_pipe(t_envar **ev, t_exeec *z);
char					**env_tab(t_envar **ev);
int						heredoc(t_commandes **c, t_varint *l, char *list, char **evir);
void					redirection(t_varint *l, char **files, char *list);
char					**split_path(t_envar **ev);
char					*check_path(char **split, char *cmd);
void					single_command(t_exeec *z, t_envar **ev);
void					single_node_exec(t_exeec *z, char *list, t_envar **ev, char **envir);
int						heredoc_single_command(t_exeec *z, char *list, char **envir);
void					child_process_in_pipe(t_exeec *z, t_envar **ev);
void					parent_process_in_pipe(t_exeec *z);
int						ft_strcmp(char *s1, char *s2);
int						env_len(t_commandes *m);
char					*var_get(t_envar *env);
char					*get_path(t_envar *env);
char					*fill_path(t_envar *env, t_env *s);
int						quotes_error(char *list);
int						expand_erreur(char *list);
int						lerreurat(int error);
char					*ft_substr(char *s, int start, int len);
char					**ft_split(char *str, char c);
t_commandes				*ft_lstnew(void *content);
t_commandes				*ft_lstlast(t_commandes *lst);
void					ft_lstadd_back(t_commandes **lst, t_commandes *new);
void					ft_lstadd_back_files(t_files **lst, t_files *new);
t_files					*ft_lstlast_files(t_files *lst);
t_files					*ft_lstnew_files(void *content);
void					int_main(t_main *main);
void					int_main_before(t_main *main, t_envar *ev);
void					int_main_after(t_main *main);
void					print_after_pipe(t_main *main);
void					do_after_pipe(t_main *main, t_envar *ev);
void					done_normal(t_commandes *tmp, t_env *senv, t_envar *env,
							t_bill *bill);
void					check_bill(t_commandes *tmp, t_env *senv, t_envar *env);
void					re_vars(t_main *main);
void					siginthandler(int signal);
int						ft_strncmp(char *s1, char *s2);
int						ft_strlen(char *str);
void					int_sig_main(t_main *main);
char					*toknz_list(char *str, int i, int j);
void					redi_tokenz(t_tokenz *m, char *str, char token);
void					double_redi_tokenz(t_tokenz *m, char *str, char token);
int						count_ptr(char *list, int bool);
int						ft_isredi(char c);
int						ft_isspecial(char c);
int						ft_isspace(char c);
int						ft_issospecial(char c);
int						ft_isprintbl(char c);
int						count_redi(char *list, int bool);
int						count_pipe(char *list);
char					**return_commande(char *list, char *str, int bool,
							int c);
int						ft_isspecial(char c);
int						find_quotes_pair(char *str, char c);
char					*ft_strjoin(char *s1, char *s2);
void					ft_putstr(char *str);
int						quote_bfr_pipe(char *str, int i, char q);
void					dquotes_tokenz(t_tokenz *m, char *str);
void					squotes_tokenz(t_tokenz *m, char *str);
void					xsqbp(t_tokenz *m, char *str);
void					dqbp(t_tokenz *m, char *str);
void					sqbp(t_tokenz *m, char *str);
void					xdfill_it(t_tokenz *m, char *str);
void					xsfill_it(t_tokenz *m, char *str);
void					xdqbp(t_tokenz *m, char *str);
int						sec_q(char *tknz);
int						sec_q_rex(char *tknz, int end);
int						frst_q(char *tknz);
int						frst_q_rex(char *tknz, int start);
char					*quotes_quotes(char *str, char *tknz, int start);
char					*fill_var(t_commandes *tmp, t_envar *env, int i, int j);
int						num_of_q(char *list, int start);
char					**return_file(char *list, char *str, int bool,
							t_commandes *m);
void					fill_the_rest(t_tokenz *m, char *str);
void					fill_the_rest2(t_tokenz *m, char *str);
void					get_end(t_commande *s, int i, char *list);
void					get_start(t_commande *s, int i, char *list);
void					last_world_ig(t_commande *s, int i);
void					get_commande(t_commande *s, char *str);
void					skip_sp(t_commande *s, char *list, int i);
void					free_all_1(char **str);
int						num_of_s_q(char *list, int start);
int						sec_s_q(char *tknz);
int						check_pipe(char *list);
void					start_stop(char *list, t_commande *s, int i);
int						starting_parss(char *list, int i, int c);
int						for_quotes(char *list, t_commande *s, char *str, int i);
void					rest_of_parss(char *list, char *str, t_commande *s,
							int i);
void					init_file_parss(char *list, t_file *f, t_commandes *m,
							int bool);
int						skip_file_parss(char *list, int i);
int						find_end_file_parss(char *list, t_file *f, int i);
void					fill_file_parss(char *str, t_commandes *m, t_file *f);
int						first_file_parss(int bool, int i);
void					rl_replace_line(const char *s, int clear_undo);
int						for_q(char *list, t_count *c, char q, int i);
void					count_it(char *list, t_count *c, int i);
void					init_count_vars(char *list, t_count *c);
void					init_quote_parss(t_quote *q);
void					init_dq_parss(char *tknz, t_quote *q, int start);
void					init_sq_parss(char *tknz, t_quote *q, int start);
void					parss_quotes(char *str, char *tknz, t_quote *q,
							char token);
void					fill_between_q(char *str, t_quote *q);
void					init_quotes_full(char *tknz, t_quote *q, int start);
char					*add_return_quote(t_quote *q);
void					plus_plus(t_tokenz *m);
void					starting(char *str, t_tokenz *m);
void					check_and_fill(char *str, t_tokenz *m);
void					fill_in_single(char *str, t_tokenz *m);
void					fill_in_double(char *str, t_tokenz *m, char token);
void					*my_malloc(size_t size);
void					my_free(void *address);
void					my_free_all(void);
void					ft_memset(void *pointer, int c, size_t len);
void					*ft_memcpy(void *destination, void *source, size_t len);
t_envar					*get_env(t_envar *head, char **env);
void	multiple_pipe(t_commandes **c, t_envar **ev, char *list, t_env **eev, char **envi);
char					*ft_itoa(int n);
void					ft_read_line(t_main *main);
void					signal_handler(void);
t_envar					*ft_ls_tnew(char *content);
void					ft_ls_tadd_back(t_envar **lst, t_envar *ne);
int						exec(t_envar **env, char **input);
void					t_export(t_envar **env, char **input);
void					t_cd(t_envar **ev, char **input);
void					t_echo(char **input);
void					t_pwd(void);
void					t_exit(char **c);
int						ft_str_ncmp(char *s1, char *s2, int n);
char					*ft_strdup(char *s1);
int						ft_strlen(char *str);
char					*ft_strjoin(char *s1, char *s2);
void					env(t_envar **ev);
void					unset(t_envar **head, char **value);
char					*ft_strcat(char *src, char	*dst);
char					*ft_str_rmc(char *src);
char					*ft_strchr(char *s, int c);
int						ft_isalpha(int c);
char					**ft_split(char *str, char c);
int						ft_isdigit(int c);
int						ft_lstsize(t_envar *lst);
int						ft_lst_size(t_commandes *lst);
int						ft_atoi(const char *str);
int						end_if_aro(t_commande *s, int i, char *list);
int						initcount(int bool, int j);
int						is_pss(char c);
void					for_aro_tok(t_tokenz *m, char *str);
char					*add_quots(char *value);
int						check_ifinput_true(char *input);
int						check_for_eq(char *s);
void					join_strings(t_envar **env, char **input, t_expo *l);
void					fir_case(t_envar **env, char **input, t_expo *l);
void					display_env_if_null(t_envar **env);
void					second_case(t_envar **env, char **input, t_expo *l);
void					third_case(t_envar **env, char **input, t_expo *l);
void					cd_old(t_envar	**ev, t_tcd *l, char **input);
void					cd_as(t_envar	**ev, t_tcd *l);
void					get_pwd(t_envar	**ev, t_tcd *l);
char					*check_bill_her(char *str, t_env *senv, t_envar *env);
void					done_normal_her(char *str, t_env *senv, t_envar *env,
							t_bill *bill);
char					*fill_var_her(char *str, t_envar *env, int i);
char					*fill_path_her(t_envar *env, t_env *s);
void					set_pipe(t_exeec *z, t_envar **ev);

void	init_z(t_exeec *z, t_commandes **c);
void	init_z_next(t_exeec *z);
int	bigger_than_one(char *list, t_commandes **c, t_exeec *z, t_envar **ev, char **envi);

#endif
