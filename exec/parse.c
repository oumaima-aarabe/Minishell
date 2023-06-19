/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/19 20:52:09 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

splitnode    *parsing(char *prompt)
{
    Node    *node;
    // int j = 1;
    node = splitstring(prompt);
    // printlist(node);
    splitnode   *tokens;
    tokens = splitdataLinkedList(node);
    freelist(node);
    // // checkquotes(tokens);
    // splitnode *current = tokens;
    // while (current != NULL)
    //  {

    //     splitnode *next = current;
    //    // Print the split data
    //     int i = 0;
    //     while (current->splitdata[i])
    //     {
    //         // printf("{{{%d}}", j++);
    //         // fflush(stdout);
    //         printf("Token %d: %s\n", i + 1, current->splitdata[i]);
    //         i++;
    //     }


    //     // Free the memory allocated for split data
    //     i = 0;
    //     while (next->splitdata[i] != NULL)
    //      {
    //         free(next->splitdata[i]);
    //         i++;
    //     }
    //     free(next->splitdata);

    //     current = next->next;
    //     free (next);
    // }
    return (tokens);
}

// int main()
// {

// 	parsing("ls -la | fghj | expand      \"     \'this\'    |    \"dsfghjfghjk   \'dfgh\'");
// }
// s_tokens    *new_node(char  *cmd)
// {
//     s_token *node = (s_token *)malloc(sizeof(s_token));

//     node->cmd = NULL;
//     node->left = NULL;
//     node->right = NULL;
//     return (node);
// }
// void    set_token(s_tokens *tokens, char *prompt, int *i, int flag)
// {
//     if (flag == 0)
//         handle_pipe(tokens, prompt, &i);
// }
// void    parse_command(char *prompt)
// {
//     s_tokens    *cmd_list;
//     char    *tmp;
//     size_t i;

//     tmp = prompt;
//     i = 0;
//     cmd_list = NULL;
//     while (*tmp)
//     {
//         if (*tmp == '|')
//             set_token(cmd_list, prompt, &i, PIPE);
//         else if (*tmp == '\"')
//             set_token(cmd_list, prompt, &i, DQ);
//         else if (*tmp == '\'')
//             set_token(cmd_list, prompt, &i, SQ);
//         else if (ft_isalnum(*tmp) || *tmp == '_' )
//             set_token(cmd_list, prompt, &i, WORD);
//         else if (*tmp == ' ')
//             sed_token(cmd_list, prompt, &i, SP);
//         else if (*tmp == '>' && *(tmp + 1) == '>')
//             red_token(cmd_list, prompt, &i, APPEND);
//         else if (*tmp == '<' *(tmp + 1) == '<')
//             red_token(cmd_list, prompt, &i, HEREDOC);
//         else if (*tmp == '>')
//             red_token(cmd_list, prompt, &i, ROUT)
//         else if (*tmp == '<')
//             red_token(cmd_list, prompt, &i, RIN);
//         *tmp += i;
//     }
// }

