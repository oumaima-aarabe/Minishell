/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:42 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/14 01:54:05 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include "readline/history.h"
# include "readline/readline.h"

// void    parse_command(char *prompt);
// char	**ft_split(char const *s, char c);
// int		ft_isalnum(int c)''


typedef enum t_flags
{
	PIPE = 15,
	DQ,
	SQ,
	WORD,
	HEREDOC,
	APPEND,
	RIN,
	ROUT,
	SPC,
	CMD,
	VAR

}           flag;

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
char	*ft_strjoin(char *s1, char *s2);
int		lexer2(char *line);


////////////////////////////////////////////////////////////////
////////////////SPLIT USING PIPES///////////////////////////////
Node	*splitstring(char *line);
void 	freenodes(Node *head);
Node* 	createnode(char* data);
int 	check_for_quotes(char* line, int index);
////////////////////////////////////////////////////////////////
/////////////////SPLIT USING SPACES///////////////////////////
splitnode   *splitdatalinkedlist(Node *originalist);
void free_split_nodes(splitnode* head);
splitnode* create_split_node(char** splitdata, int word_count);
char** split_string(char* str, int* word_count);
int count_words(char* str);
int is_inside_quotes(char* str);

// void printlist(Node *head);
void    parsing(char *prompt);
void  hendl_ctr_c(int sig);
void	*my_realloc(void *ptr, size_t new_size);
void	*ft_calloc(size_t count, size_t size);
void checkquotes(splitnode *list);
char	*ft_strtrim(char *s1, char *set);
char    *ft_strcat(char *destination, const char    *source);
int check_char(char c);




#endif