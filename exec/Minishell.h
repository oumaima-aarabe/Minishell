/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:42 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/14 01:54:05 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef minishell_H
# define minishell_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdint.h>
#include <errno.h>

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

int ex_s;

int		lexer(char *line);
int		lexer2(char *line);
void	ft_syntax_err(void);
char	*ft_strjoin(char *s1, char *s2);
int		lexer2(char *line);
Node	*splitstring(char *line);
void 	freelist(Node *head);
splitnode   *splitdataLinkedList(Node *originalist);
void printlist(Node *head);
splitnode    *parsing(char *prompt);
void  hendl_ctr_c(int sig);
void	*my_realloc(void *ptr, size_t new_size);
void	*ft_calloc(size_t count, size_t size);
void checkquotes(splitnode *list);
char	*ft_strtrim(char *s1, char *set);
char    *ft_strcat(char *destination, const char    *source);

void	ft_lstadd_back(t_env **alst, t_env *new);
void	ft_lstclear(t_env **alist);
void	ft_putstr_fd(char *s, int fd);
void	ft_free_(char **tab);
void	ft_exec(splitnode *cmd, t_env *en);
void	ft_print_err(char *cmd, char *st);


char	*ft_strjoin(char *s1, char *s2); // free
char	*ft_strdup(char *s1);
char	*ft_substr(char const *s,  int start, int len);
char	**ft_split(char *st, char c);
char	*ft_itoa(int n);



int	ft_strcmp(char	*s1, char	*s2);
int	ft_strlen(char const *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_execut_bultins(splitnode *cmd, t_env *env);
int	ft_atoi(char *str);
int ft_sine(char *st, char c);


t_env	*ft_creat(char *key, char *val);
t_env	*duplicate_linked_list(t_env *last);


#endif
