/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:49:51 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/23 00:50:26 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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


// Structure to represent a command node in the history
struct CommandNode {
    char* command;
    struct CommandNode* prev;
    struct CommandNode* next;
};

// Structure to encapsulate the shell's state
struct ShellState {
    struct CommandNode* history_head;
    struct CommandNode* history_tail;
};

#endif