/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:33:01 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 03:44:38 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_Node	*createnode(char *data)
{
	t_Node	*newnode;

	newnode = (t_Node *)malloc(sizeof(t_Node)); // ! ptrotecti malloc
	newnode->data = ft_strdup(data);
	newnode->prev = NULL;
	newnode->next = NULL;
	return (newnode);
}

int	_dquotes(char *line, int index)
{
	int		inquotes;
	int		i;
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	inquotes = 0;
	i = 0;
	while (i < index)
	{
		cq = check_quotes(cq, i, line);
		if (line[i] == '"' && !cq.ins)
			inquotes = !inquotes;
		i++;
	}
	return (!inquotes);
}

int	_squotes(char *line, int index)
{
	int		inquotes;
	int		i;
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	inquotes = 0;
	i = 0;
	while (i < index)
	{
		cq = check_quotes(cq, i, line);
		if (line[i] == '\'' && !cq.ind)
			inquotes = !inquotes;
		i++;
	}
	return (!inquotes);
}

t_Node	*splitstring_loop(t_Node **tail, int length, char *line, int *start)
{
	t_Node	*head;
	int		i;

	i = -1;
	head = NULL;
	while (++i < length)
	{
		if (line[i] == '|' && (_squotes(line, i) && _dquotes(line, i)))
		{
			line[i] = '\0';
			if (head == NULL)
			{
				head = createnode(&line[*start]);
				*tail = head;
			}
			else
			{
				(*tail)->next = createnode(&line[*start]);
				(*tail)->next->prev = (*tail);
				(*tail) = (*tail)->next;
			}
			*start = i + 1;
		}
	}
	return (head);
}

t_Node	*splitstring(char *line)
{
	t_Node	*head;
	t_Node	*tail;
	int		start;
	int		length;

	length = ft_strlen(line);
	start = 0;
	head = NULL;
	tail = NULL;
	head = splitstring_loop(&tail, length, line, &start);
	if (head == NULL)
	{
		head = createnode(line);
		tail = head;
	}
	else
	{
		tail->next = createnode(&line[start]);
		tail->next->prev = tail;
		tail = tail->next;
	}
	return (head);
}
