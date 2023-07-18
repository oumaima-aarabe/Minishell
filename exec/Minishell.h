/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:42 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 12:36:33 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdint.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/ioctl.h>

/////////////////////////////////3lachghenat///////////////////////////

typedef struct s_spex
{
	char			*expanded;
	char			*quotesremoved;
	char			**splitted;
	int				k;
	int				i;
}	t_spex;

typedef struct s_exv
{
	char	*tmp;
	char	*new;
	char	*value;
	char	*expanded;
	int		len;
	int		pos;
}	t_exv;

typedef struct s_quotes
{
	int	i;
	int	j;
	int	ins;
	int	ind;
	int	word_index;
	int	changed;
	int	in_word;
	int	count;
	int	wc;
	int	z;
	int	print;
	int	start;
	int	length;
}	t_quote;

typedef struct s_env
{
	char			*key;
	char			*valu;
	struct s_env	*next;
}	t_env;

typedef struct s_fds
{
	int	in;
	int	out;
	int	fd_in;
	int	fd_out;
}	t_fds;

typedef struct s_hd
{
	int	i;
	int	j;
	int	count;
	int	print;
	int	k;
	int	z;
	int	wc;
	int	contin;
	int indx;
}	t_hd;

typedef struct s_gs
{
	t_env	*env;
	int		ex_s;
	int		sig_flag;
	int		red_flag;
	char	*pwd;
}	t_gs;

t_gs	g_v;

/////////////////////////////////////////////////////////////////////
///////// Structure for doubly linked list node//////////////////////
typedef struct Node {
	char		*data;
	struct Node	*prev;
	struct Node	*next;
}	t_Node;

typedef struct splitnode {
	char				**splitdata;
	struct splitnode	*prev;
	struct splitnode	*next;
	int					in;
	int					out;
	int					flag;
}	t_splitnode;

typedef struct manp {
	t_Node	*head;
	t_Node	*tail;
}	t_manp;

int				check_red1(char *line);
int				check_red2(char *line);
int				check_pipe(char *line);
int				valid_quotes(char *line);

void			ft_syntax_err(void);

////////////////////////////////////////////////////////////////
////////////////SPLIT USING PIPES///////////////////////////////

t_Node			*splitstring(char *line);
t_Node			*createnode(char	*data);
void			freenodes(t_Node *head);
int				check_for_quotes(char	*line, int index);

////////////////////////////////////////////////////////////////
/////////////////SPLIT USING SPACES/////////////////////////////

t_splitnode		*splitdatalinkedlist(t_Node *originalist);
t_splitnode		*create_split_node(char **splitdata);

void			free_split_nodes(t_splitnode *head);
char			**split_string(char *str, t_quote cq);
int				count_words(char *str, t_quote cq);
int				is_inside_quotes(char *str);

////////////////////////////////////////////////////////////////
/////////////////HANDLE REDIRECTIONS////////////////////////////

t_splitnode		*handle_redirections(t_splitnode *node, t_env *env);
t_splitnode		*create_new_node(char **splitdata, int in, int out);
int				word_count(char **cmdl);
char			**newstring(char **cmdl, int wc);
t_splitnode		*remove_redirections(t_splitnode *node, int hr);
bool			is_quote(char c);
int				get_fl(char *str);
bool			is_redirection(char ch);

// void		parsing(char *prompt, t_env *env);
t_splitnode		*parsing(char *prompt, t_env *env);
void			hendl_ctr_c(int sig);
void			*ft_calloc(size_t count, size_t size);
char			**checkquotes(char **list, t_env *env);
char			*ft_strtrim(char *s1, char *set);
char			*get_1redfilen(int *i, int *j, char **cmd_l, t_env *env);
char			*get_2redfilen(int *i, int *j, char **cmd_l, t_env *env);

////////////////////////////////////////////////////////////////
///////////////////////HEREDOC//////////////////////////////////

t_splitnode		*read_hd(t_splitnode *current, int *i, int *j, t_env *env);
t_splitnode		*handle_heredoc(t_splitnode *node, t_env *env);
int				wc_heredoc(char **cmdl);
char			**ns_heredoc(char **cmdl, int wc);

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

int				ft_strlen(char *str);
char			*ft_substr(char *s, int start, int len);
void			ft_putstr_fd(char *s, int fd);
int				ft_strncmp( char *s1, char *s2, size_t n);
char			*ft_strdup( char *s1);
int				ft_strcmp(char *s1, char *s2);
char			**ft_split(char *st, char c);
int				ft_atoi(char *str);
char			*ft_itoa(int n);

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

t_env			*ft_creat(char *key, char *val);
void			ft_lstadd_back(t_env **alst, t_env *new);
t_env			*duplicate_linked_list(t_env *last);
void			ft_lstclear(t_env **alist);
int				ft_lstsize(t_env *env);

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

char			*removequotes(char	*input);
char			*ft_expand(char *cmd, t_env *en);

//---------------------------------------------------------------//

void			execution(t_splitnode *cmd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_free_(char **tab);
void			ft_exec(char **cm, t_env *en);
void			ft_print_err(char *cmd, char *st);

char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s1);
char			**ft_split(char *st, char c);
int				ft_execut_cmd(t_splitnode *cmd);
int				ft_execut_bultins(char **cmd);
int				ft_signe(char *st, char c);

int				ft_add_export(char *cmd);
void			ft_shelvl(t_env *env);
void			environment(char **env);
char			*ft_take_key(char *str, t_env *env, int j, int len);

t_quote			check_quotes(t_quote check_q, int j, char *cmd);
t_quote			init_q(void);
int				_dquotes(char *line, int index);
int				_squotes(char *line, int index);
void			ft_execut_cd(char *str, t_env *env);
char			**ft_joindstrs_at(char **ds1, char **ds2, int at);
int				ft_dstrlen(char **dstr);
int				ft_invalid_export_unset(char *cmd, char *bult);
void			ft_execut_export(char **cmd);
void			*ft_memset(void *b, int c, size_t len);
int				ft_isalpha(int c);
int				ft_isalnum(int c);

void			read_inhd(char *lmtr, int k, int fd, t_env *env);
void	ft_free_plus(char *s1, char *s2, void *s3);
void	ft_remov_lis(char *cmd);
void	ft_execut_env(t_env *env, char **cmd);
int	ft_atoi_exit(char *str, int i);


char	*is_valid_cmd(char **path, char *cmd);
char	*ft_prepar_path(char *cmd);
char	**ft_get_path(t_env *env);
char	*is_path_exec(char *cmd);
char	**ft_my_env(t_env *env, int i);

void	ft_exucve(char *cmd, char **arg, char **env);
int	compar(int a, int b);
int	ft_check_old_env(char *cmd);
int	ft_check_add_export(char **cmd, int i);
t_env	*ft_sort_export(t_env *tmp);
int	ft_isnum(int c);
int	ft_cd_execut(char *str, char *hom, char *old);
int	ft_check_getcwd(void);
void	ft_change_env(t_env *env, char *old);
int	fork_execut(t_splitnode *ptr, t_fds pipe, t_env *env);
int	ft_one_cmd(t_splitnode *cmd, t_env *env, int fd_in, int fd_out);


void	red_input(t_splitnode **node, int *i, int *j, t_env *env);
void	red_append(t_splitnode **node, int *i, int *j, t_env *env);
void	red_output(t_splitnode **node, int *i, int *j, t_env *env);
t_quote	skip_red(t_quote cq, char **cmdl);
t_hd	check_dprintable(char **cmdl, t_quote cq, t_hd hd);
char	**split_expanded(char *str);



#endif
