/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 07:37:42 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 07:39:07 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


t_splitnode	*create_split_node(char   **splitdata)
{
	t_splitnode	*new_split_node;

	new_split_node = ft_calloc(1, sizeof(t_splitnode));
	if(!new_split_node)
		return (NULL);
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
