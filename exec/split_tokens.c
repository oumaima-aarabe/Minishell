/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:39:36 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/16 02:43:11 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int count_words(char *str) 
{
	t_quote cq;
	
	ft_memset(&cq, 0, sizeof(t_quote));
	cq.length = ft_strlen(str);
	while (cq.i < cq.length) 
	{
		if ((str[cq.i] == ' ' || str[cq.i] == '\t') && !cq.in_word && (!cq.in_squotes || !cq.in_dquotes)) 
		{
			cq.i++;
			continue;
		}
		if ((str[cq.i] == '"' && !cq.in_squotes) || (str[cq.i] == '\'' && !cq.in_dquotes))
			cq = check_quotes(cq, cq.i, str);
			
		else if ((str[cq.i] == ' ' || str[cq.i] == '\t') && (!cq.in_squotes && !cq.in_dquotes))
		{
			cq.in_word = 0;
			cq.count++;
		}
		else
			cq.in_word = 1;
		cq.i++;
	}
	if (cq.in_word)
		cq.count++;
	return (cq.count);
}

char	*fill_array(char *str, t_quote cq)
{
	char *array;
	
	array = (char *)calloc((cq.i - cq.start_index + 1) , sizeof(char));
	if (!array)
		return (NULL);
	strncpy(array, &str[cq.start_index], cq.i - cq.start_index);
	// array[cq.i - cq.start_index] = '\0';
	return (array);
}

/////////////////////////////////////////////////////////
char **split_string(char *str) 
{
	t_quote cq;
	char **words;
	
	ft_memset(&cq, 0, sizeof(t_quote));
	cq.length = ft_strlen(str);
	cq.count = count_words(str);
	words = (char **)calloc((cq.count + 1) , sizeof(char *));
	if (!words)
		return (NULL);
	while (cq.i < cq.length && (str[cq.i] == ' ' || str[cq.i] == '\t'))
		cq.i++;
	cq.start_index = cq.i;
	while (cq.i <= cq.length && cq.word_index < cq.count) 
	{
		if ((str[cq.i] == ' ' || str[cq.i] == '\t' || str[cq.i] == '\0') && (!cq.in_squotes && !cq.in_dquotes)) 
		{
			if (cq.in_word) 
			{
				words[cq.word_index] = fill_array(str, cq);
				cq.word_index++;
				cq.in_word = 0;
			}
			cq.start_index = cq.i + 1;
		}
		 else if ((str[cq.i] == '"' && !cq.in_squotes) || (str[cq.i] == '\'' && !cq.in_dquotes)) 
			cq = check_quotes(cq, cq.i, str);
		else 
			cq.in_word = 1;
		cq.i++;
	}
	return words;
}

/////////////////////////////////////////////////////////
t_splitnode   *create_split_node(char   **splitdata) 
{
	t_splitnode   *new_split_node = calloc(1, sizeof(t_splitnode));
	new_split_node->splitdata = splitdata;
	new_split_node->prev = NULL;
	new_split_node->next = NULL;
	new_split_node->in = -1;
	new_split_node->out = -1;
	return new_split_node;
}

t_splitnode   *splitdatalinkedlist(t_Node  *original_list) 
{
	t_splitnode   *head = NULL;
	t_splitnode   *tail = NULL;

	t_Node    *current = original_list;
	while (current != NULL) 
	{
		char    **splitdata = split_string(current->data);
		t_splitnode   *new_node = create_split_node(splitdata);
		if (head == NULL) 
		{
			head = new_node;
			tail = head;
		}
		else 
		{
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
		current = current->next;
	}
	return head;
}
