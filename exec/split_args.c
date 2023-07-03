/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:33:01 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/03 10:03:02 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_Node	*createnode(char *data)
{
	t_Node	*newnode;

	newnode = (t_Node *)malloc(sizeof(t_Node));
	newnode->data = strdup(data);
	newnode->prev = NULL;
	newnode->next = NULL;
	return (newnode);
}

int	check_for_quotes(char *line, int index)
{
	int	inquotes;
	int	i;

	inquotes = 0;
	i = 0;
	while (i < index)
	{
		if (line[i] == '"' || line[i] == '\'')
			inquotes = !inquotes;
		i++;
	}
	return (!inquotes);
}


t_Node	*splitstring(char* line) 
{
    t_Node	*head = NULL;
    t_Node	*tail = NULL;
    int length = ft_strlen(line);
    int i = 0;
    int start = 0;

    while (i < length) 
    {
        if (line[i] == '|' && check_for_quotes(line, i)) 
        {
            line[i] = '\0';
            if (head == NULL) 
            {
                head = createnode(&line[start]);
                tail = head;
            } 
            else 
            {
                tail->next = createnode(&line[start]);
                tail->next->prev = tail;
                tail = tail->next;
            }
            start = i + 1;
        }
        i++;
    }
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

    return head;
}

// t_Node	*create_update(t_Node *head, t_Node **tail, char *data)
// {
// 	if (head == NULL)
// 	{
// 		head = createnode(data);
// 		*tail = head;
// 	}
// 	else
// 	{
// 		(*tail)->next = createnode(data);
// 		(*tail)->next->prev = *tail;
// 		*tail = (*tail)->next;
// 	}
// 	return (head);
// }

// t_Node	*process_s(char *line, t_Node **tail)
// {
// 	t_Node	*head;
// 	int		length;
// 	int		i;
// 	int		start;

// 	head = NULL;
// 	length = ft_strlen(line);
// 	i = 0;
// 	start = 0;
// 	while (i < length)
// 	{
// 		if (line[i] == '|' && check_for_quotes(line, i))
// 		{
// 			line[i] = '\0';
// 			head = create_update(head, tail, &line[start]);
// 			start = i + 1;
// 		}
// 		i++;
// 	}
// 	head = create_update(head, tail, &line[start]);
// 	return (head);
// }

// t_Node	*splitstring(char *line)
// {
// 	t_Node	*head;
// 	t_Node	*tail;

// 	head = NULL;
// 	tail = NULL;
// 	head = process_s(line, &tail);
// 	if (head == NULL)
// 	{
// 		head = createnode(line);
// 		tail = head;
// 	}
// 	else
// 	{
// 		tail->next = createnode(line);
// 		tail->next->prev = tail;
// 		tail = tail->next;
// 	}
// 	return (head);
// }
