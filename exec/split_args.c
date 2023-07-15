/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:33:01 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/15 11:41:17 by ouaarabe         ###   ########.fr       */
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

int	_dquotes(char *line, int index)
{
	int	inquotes;
	int	i;

	inquotes = 0;
	i = 0;
	while (i < index)
	{
		if (line[i] == '"')
			inquotes = !inquotes;
		i++;
	}
	return (!inquotes);
}

int	_squotes(char *line, int index)
{
	int	inquotes;
	int	i;

	inquotes = 0;
	i = 0;
	while (i < index)
	{
		if (line[i] == '\'')
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
        if (line[i] == '|' && (_squotes(line, i) && _dquotes(line, i))) 
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


