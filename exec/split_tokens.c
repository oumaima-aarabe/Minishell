/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:39:36 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 03:49:57 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	count_words(char *str, t_quote cq)
{
	while (cq.i < cq.length)
	{
		if ((str[cq.i] == ' ' || str[cq.i] == '\t') && \
		!cq.in_word && (!cq.ins || !cq.ind))
		{
			cq.i++;
			continue ;
		}
		if ((str[cq.i] == '"' && !cq.ins) || \
		(str[cq.i] == '\'' && !cq.ind))
			cq = check_quotes(cq, cq.i, str);
		else if ((str[cq.i] == ' ' || str[cq.i] == '\t') && \
		(!cq.ins && !cq.ind))
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

	array = (char *)calloc((cq.i - cq.start + 1) , sizeof(char)); // ! ha wa7d calloc
	if (!array)
		return (NULL);
	strncpy(array, &str[cq.start], cq.i - cq.start); // ! strncpy
	return (array);
}

char	**split_string_loop(t_quote cq, char *str, char **words)
{
	while (cq.i <= cq.length && cq.word_index < cq.count)
	{
		if ((str[cq.i] == ' ' || str[cq.i] == '\t' || \
		str[cq.i] == '\0') && (!cq.ins && !cq.ind))
		{
			if (cq.in_word)
			{
				words[cq.word_index] = fill_array(str, cq);
				cq.word_index++;
				cq.in_word = 0;
			}
			cq.start = cq.i + 1;
		}
		else if ((str[cq.i] == '"' && !cq.ins) || \
		(str[cq.i] == '\'' && !cq.ind))
			cq = check_quotes(cq, cq.i, str);
		else
			cq.in_word = 1;
		cq.i++;
	}
	return (words);
}

char	**split_string(char *str, t_quote cq)
{
	char	**words;

	cq.count = count_words(str, cq);
	words = (char **)calloc((cq.count + 1) , sizeof(char *)); // ! calloc
	if (!words)
		return (NULL);
	while (cq.i < cq.length && (str[cq.i] == ' ' || str[cq.i] == '\t'))
		cq.i++;
	cq.start = cq.i;
	words = split_string_loop(cq, str, words);
	return (words);
}

t_splitnode	*create_split_node(char   **splitdata)
{
	t_splitnode	*new_split_node = calloc(1, sizeof(t_splitnode)); // !calloc o mamprotectiach
	new_split_node->splitdata = splitdata;
	new_split_node->prev = NULL;
	new_split_node->next = NULL;
	new_split_node->in = -1;
	new_split_node->out = -1;
	return (new_split_node);
}


t_splitnode	*split_loop(t_splitnode **tail, t_quote cq, t_Node *current)
{
	t_splitnode	*head;
	char		**splitdata;

	head = NULL;
	while (current != NULL)
	{
		cq.length = ft_strlen(current->data);
		splitdata = split_string(current->data, cq);
		t_splitnode	*new_node = create_split_node(splitdata);
		if (head == NULL)
		{
			head = new_node;
			(*tail) = head;
		}
		else
		{
			(*tail)->next = new_node;
			new_node->prev = (*tail);
			(*tail) = new_node;
		}
		current = current->next;
	}
	return head;
}

t_splitnode *splitdatalinkedlist(t_Node  *original_list)
{
	t_splitnode	*head;
	t_splitnode	*tail;
	t_Node		*current;
	t_quote		cq;

	current = original_list;
	head = NULL;
	tail = NULL;
	ft_memset(&cq, 0, sizeof(t_quote));
	head = split_loop(&tail, cq, current);
	return (head);
}
