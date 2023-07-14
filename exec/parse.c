/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/14 08:40:12 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char **split_expanded(char *str, int word_count) {
	int length = ft_strlen(str);
	int count = 0;
	int in_word = 0;
	int s_quotes = 0;
	int d_quotes = 0;
	int i = 0;
	// Count the number of words
	while (i < length) 
	{
		if ((str[i] == ' ' || str[i] == '\t') && (!s_quotes && !d_quotes))
		{
			if (in_word) {
				count++;
				in_word = 0;
			}
		}
		else if (str[i] == '"' &&  !s_quotes) 
		{
		
			d_quotes = !d_quotes;
			in_word = 1;
		}
		else if (str[i] == '\'' && !s_quotes) 
		{
			s_quotes = !s_quotes;
			in_word = 1;
		}
		 else
			in_word = 1;
		i++;
	}

	if (in_word)
		count++;
	char **words = (char **)calloc((count + 1) , sizeof(char *));
	int word_index = 0;
	int start_index = 0;
	in_word = 0;
	s_quotes = 0;
	d_quotes = 0;
	i = 0;

	// Skip leading whitespace
	while (i < length && (str[i] == ' ' || str[i] == '\t'))
		i++;

	start_index = i;

	while (i <= length) 
	{
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\0') && (!s_quotes && !d_quotes)) 
		{
			if (in_word) 
			{
				words[word_index] = (char *)calloc((i - start_index + 1) , sizeof(char));
				strncpy(words[word_index], &str[start_index], i - start_index);
				words[word_index][i - start_index] = '\0';
				word_index++;
				in_word = 0;
			}
			start_index = i + 1;
		}
		 else if (str[i] == '"' && !s_quotes) 
		{
			d_quotes = !d_quotes;
			in_word = 1;
		}
		else if (str[i] == '\'' && !d_quotes) 
		{
			s_quotes = !s_quotes;
			in_word = 1;
		}
		else 
			in_word = 1;
		i++;
	}

	words[word_index] = NULL;
	word_count = count;
	return words;
}

int	check_for_space(char *expanded)
{
	t_quote cq;
	int i;

	i = 0;
	memset(&cq, 0, sizeof(t_quote));
	while(expanded[i])
	{
		cq = check_quotes(cq, i, expanded);
		if(!cq.in_dquotes && !cq.in_squotes && expanded[i] == ' ')
		{
					puts("here\n");
			
			return(1);
		}
		i++;
	}
	return(0);
}

char	**apply_ex_q(char **splitdata, t_env *en)
{
	int		i;
	// int		k;
	char	*expanded;
	char	*quotesremoved;
	char	**splitted = NULL;

	i = 0;
	if (splitdata)
	{
		if (splitdata[i])
		{
			while (splitdata[i])
			{
				expanded = ft_expand(splitdata[i], en);
				splitdata[i] = expanded;
				if (check_for_space(expanded))
				{
					splitted = split_expanded(expanded, count_words(expanded));
					// k = ft_double_strlen(splitted);
					splitdata = ft_joindstrs_at(splitdata, splitted, i);
					// i += k;
				}
				if (splitdata[i])
					i++;
			}
			i = 0;
			while (splitdata[i])
			{
				
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
        current->splitdata = splitdata;
		current = current->next;
	}
	return (head);
}

// t_splitnode	*parsing(char	*prompt, t_env *env)
// {
// 	t_Node		*node;
// 	t_splitnode	*tokens;

// 	node = splitstring(prompt);
// 	tokens = splitdatalinkedlist(node);
// 	freenodes(node);
// 	tokens = handle_heredoc(tokens, env);
// 	tokens = handle_redirections(tokens, env);
// 	iteratelist(tokens, env);
// 	return (tokens);
// }

void	parsing(char	*prompt, t_env *env)
{
	t_Node		*node;
	t_splitnode	*tokens;

	node = splitstring(prompt);
	tokens = splitdatalinkedlist(node);
	freenodes(node);
	tokens = handle_heredoc(tokens, env);
	tokens = handle_redirections(tokens, env);
	iteratelist(tokens, env);
    t_splitnode *current = tokens;

	while (current != NULL)
     {

        t_splitnode *next = current;
        // Print the split data
        int i = 0;
        while (current->splitdata[i]) 
        {
            // printf("{{{%d}}", j++);
            // fflush(stdout);
            printf("Token %d: %s\n", i + 1, current->splitdata[i]);
            i++;
        }
        // Free the memory allocated for split data
        i = 0;
        while (next->splitdata[i] != NULL)
         {
            free(current->splitdata[i]);
            i++;
        }
        free(current->splitdata);

        current = current->next;
        current = next->next;
        free (next);
            // exit(1);
    }
	// return (tokens);
}