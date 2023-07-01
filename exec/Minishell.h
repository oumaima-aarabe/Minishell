/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:42 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/25 23:55:55 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef minishell_H
# define minishell_H

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

// void    parse_command(char *prompt);
// char	**ft_split(char const *s, char c);
// int		ft_isalnum(int c)''

/////////////////////////////////3lachghenat///////////////////////////

typedef struct s_env
{
	char *key;
	char *valu;
	struct s_env *next;
}   t_env;


typedef struct s_fds
{
	int in;
	int out;
	int fd_in;
	int fd_out;
}	t_fds;



typedef struct  s_gs{
	t_env *env;
	int ex_s;
}	t_gs;

extern t_gs	g_v;

/////////////////////////////////////////////////////////////////////
typedef enum t_flags
{
	PIPE,
	DQ,
	SQ,
	WORD,
	SP,
	HEREDOC,
	APPEND,
	RIN,
	ROUT
}           flag;

// typedef struct command_list{
// 	char 	**cmd;
// 	int		in;
// 	int		out;
// 	int		flag;
// }cmd_l;

// Structure for doubly linked list node
typedef struct Node {
    char *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct splitnode {
    char **splitdata;
    struct splitnode *prev;
    struct splitnode *next;
	int		in;
	int		out;
	int		flag;
} splitnode;


typedef struct  t_tokens{
	int 	flag;
	char	*cmd;
	struct t_tokens *right;
	struct t_tokens *left;
}s_tokens;



int		lexer(char *line);
int		lexer2(char *line);
void	ft_syntax_err(void);
// char	*ft_strjoin(char *s1, char *s2);


////////////////////////////////////////////////////////////////
////////////////SPLIT USING PIPES///////////////////////////////
Node	*splitstring(char *line);
void 	freenodes(Node *head);
Node* 	createnode(char* data);
int 	check_for_quotes(char* line, int index);
////////////////////////////////////////////////////////////////
/////////////////SPLIT USING SPACES/////////////////////////////
splitnode   *splitdatalinkedlist(Node *originalist);
void free_split_nodes(splitnode* head);
splitnode* create_split_node(char** splitdata, int word_count);
char** split_string(char* str, int* word_count);
int count_words(char* str);
int is_inside_quotes(char* str);

////////////////////////////////////////////////////////////////
/////////////////HANDLE REDIRECTIONS////////////////////////////
splitnode  *handle_redirections(splitnode  *node, t_env *env);
splitnode   *create_new_node(char   **splitdata, int in, int out);
int 		word_count(char **cmdl);
char 		**newstring(char **cmdl, int wc);
splitnode* remove_redirections(splitnode* node);
bool is_quote(char c);
int get_fl(const char *str);
void later();

splitnode    *parsing(char *prompt, t_env *env);
void  hendl_ctr_c(int sig);
void	*my_realloc(void *ptr, size_t new_size);
void	*ft_calloc(size_t count, size_t size);
char 	**checkquotes(char **list, t_env *env);
char	*ft_strtrim(char *s1, char *set);
char    *ft_strcat(char *destination, const char    *source);
int check_char(char c);
char *get_redfilen(int *i, int *j, char **cmd_l, char *which_red, t_env *env);

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// char **ft_expend(char **cmd, t_env *en);
int ft_strlen(char const *str);
char	*ft_substr(char *s,  int start, int len);
void	ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup( char *s1);
int	ft_strcmp(char	*s1, char	*s2);
void	ft_free_(char **tab);
char	**ft_split(char  *st, char c);
int	ft_atoi(char *str);
char	*ft_itoa(int n);

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

t_env *ft_creat(char *key, char *val);
void	ft_lstadd_back(t_env **alst, t_env *new);
t_env *duplicate_linked_list(t_env *last);
void	ft_lstclear(t_env **alist);
int ft_lstsize(t_env *env);

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

char	*removequotes(char	*input);
char *ft_expand(char *cmd, t_env *en);



//--------------------------------------------------------------------------------------------------------


void	execution(splitnode *cmd);
// void	ft_lstadd_back(t_env **alst, t_env *new);
// void	ft_lstclear(t_env **alist);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_(char **tab);
void	ft_exec(char **cm, t_env *en);
void	ft_print_err(char *cmd, char *st);


char	*ft_strjoin(char *s1, char *s2); // free
char	*ft_strdup(char *s1);
// char	*ft_substr(char const *s,  int start, int len);
char	**ft_split(char *st, char c);
// char	*ft_itoa(int n);


int ft_execut_cmd(splitnode *cmd);
// int ft_lstsize(t_env *env);
// int	ft_strcmp(char	*s1, char	*s2);
// int	ft_strlen(char const *str);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_execut_bultins(char **cmd);
// int	ft_atoi(char *str);
int ft_sine(char *st, char c);


// t_env	*ft_creat(char *key, char *val);
// t_env	*duplicate_linked_list(t_env *last);





#endif
