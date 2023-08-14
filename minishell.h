/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:49 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/14 05:47:06 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minis/minishell.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
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

typedef struct EnvVar
{
	char				*value;
	struct EnvVar		*next;
}						envar;

typedef struct global
{
	int					exit_status;
	int					readline;
	int					child;
	int					heredoc;
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
	envar				*env_export;
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

int						env_len(t_commandes *m);
char					*var_gett(envar *env);
char					*get_path(envar *env);
char					*fill_path(envar *env, t_env *s);

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
void					int_main_before(t_main *main, envar *ev);
void					int_main_after(t_main *main);
void					print_after_pipe(t_main *main);
void					do_after_pipe(t_main *main, envar *ev);

void					done_normal(t_commandes *tmp, t_env *senv, envar *env,
							t_bill *bill);
void					check_bill(t_commandes *tmp, t_env *senv, envar *env);
void					re_vars(t_main *main);
void					siginthandler(int signal);

int						ft_strncmp(char *s1, char *s2);
int						ft_strlen(char *str);

void					int_sig_main(t_main *main);
// t_node					*create_node(int arg);
// t_node				*create_ll(char *str);
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
// int						get_index(int *list);
// char					*in_quotes(char *tokenz, char *str, int i);
int						find_quotes_pair(char *str, char c);
// int						*return_string(t_node *list, char *str);
char					*ft_strjoin(char *s1, char *s2);
void					ft_putstr(char *str);
// int						count_token(char *list);
int						quote_bfr_pipe(char *str, int i, char q);
void					dquotes_tokenz(t_tokenz *m, char *str);
void					squotes_tokenz(t_tokenz *m, char *str);
void					xsqbp(t_tokenz *m, char *str);
void					dqbp(t_tokenz *m, char *str);
void					sqbp(t_tokenz *m, char *str);
void					xdfill_it(t_tokenz *m, char *str);
void					xsfill_it(t_tokenz *m, char *str);
void					xdqbp(t_tokenz *m, char *str);
// void					fill_strct(char **commande);
int						sec_q(char *tknz);
int						sec_q_rex(char *tknz, int end);
int						frst_q(char *tknz);
int						frst_q_rex(char *tknz, int start);
char					*quotes_quotes(char *str, char *tknz, int start);
char					*fill_var(t_commandes *tmp, envar *env, int i, int j);
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
envar					*get_env(envar *head, char **env);
void					multiple_pipe(t_commandes **c, envar **ev, char *list);

char					*ft_itoa(int n);
int						end_if_aro(t_commande *s, int i, char *list);
int						initcount(int bool, int j);
int						is_pss(char c);
void					for_aro_tok(t_tokenz *m, char *str);

char					*store_var(t_commandes *tmp, t_bill *bill);
envar					*go_last(envar *env);
void					ft_lstadd_back_var(envar **lst, envar *new);
envar					*ft_lstlast_var(envar *lst);
envar					*ft_lstnew_var(void *content);

void					init_hered_var(t_herdc *a, t_commandes **c, t_varint *l,
							char *list);
int						parent_heredoc(t_herdc *a, t_varint *l);
void					fill_sring(t_varint *l, t_herdc *a);
int						bigger_than_one(char *list, t_commandes **c, t_exeec *z,
							t_envar **ev);
#endif
