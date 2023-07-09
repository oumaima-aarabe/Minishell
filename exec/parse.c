/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/09 22:02:56 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_gs	g_v;

char	**apply_ex_q(char **splitdata, t_env *en)
{
	int		i;
	char	*expanded;
	char	*quotesremoved;

	i = 0;
	if (splitdata)
	{
		if (splitdata[i])
		{
			while (splitdata[i])
			{
				expanded = ft_expand(splitdata[i], en);
				splitdata[i] = expanded;
				quotesremoved = removequotes(splitdata[i]);
				splitdata[i] = quotesremoved;
				i++;
			}
		}
	}
	return (splitdata);
}

t_splitnode	*iteratelist(t_splitnode *head, t_env *en)
{
	t_splitnode	*current;
	char		**splitdata;

	current = head;
	while (current != NULL)
	{
		splitdata = current->splitdata;
		splitdata = apply_ex_q(splitdata, en);
		current = current->next;
	}
	return (head);
}

t_splitnode	*parsing(char	*prompt, t_env *env)
{
	t_Node		*node;
	t_splitnode	*tokens;

	node = splitstring(prompt);
	tokens = splitdatalinkedlist(node);
	freenodes(node);
	tokens = handle_heredoc(tokens, env);
	tokens = handle_redirections(tokens, env);
	iteratelist(tokens, env);
	return (tokens);
}

// void parsing(char* prompt, t_env *env) 
// {
//     t_Node* node = splitstring(prompt);
//     t_splitnode* tokens = splitdatalinkedlist(node);
//     freenodes(node);

// 	tokens = handle_heredoc(tokens, env);
//     tokens = handle_redirections(tokens, env);
//     iteratelist(tokens, env);
//     t_splitnode *current = tokens;
//     while (current != NULL) 
//     {
//         t_splitnode* next = current->next;

//         // Print the split data
//         int i = 0;
//         // current->splitdata = apply_ex_q(current->splitdata, env);
//         while (current->splitdata[i]) 
//         {
//             printf("Token %d: .%s.\n", i + 1, current->splitdata[i]);
//             i++;
//         }
//         printf("red : %d||%d\n", current->in, current->out);
//         // Free the split data
//         i = 0;
//         while (current->splitdata[i] != NULL) 
//         {
//             free(current->splitdata[i]);
//             i++;
//         }
//         free(current->splitdata);
//         free(current);
//         current = next;
//     }
// }