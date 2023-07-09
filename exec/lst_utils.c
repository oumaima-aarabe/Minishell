/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:51:59 by azarda            #+#    #+#             */
/*   Updated: 2023/07/09 19:53:12 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_env	*ft_creat(char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
						// printf("-->> %s\n", key);
						// printf("-->> %s\n", val);

		new->key = key;
		new->valu = val;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*ptr;

	if (alst)
	{
		if (*alst == NULL)
		{
			*alst = new;
			new = NULL;
		}
		else
		{
			ptr = *alst;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = new;
		}
	}
}

t_env	*duplicate_linked_list(t_env *last)
{
	t_env	*nhead;
	t_env	*tail;
	t_env	*nnode;

	nhead = NULL;
	tail = NULL;
	nnode = NULL;
	if (!last)
		return (NULL);
	while (last)
	{
		nnode = ft_creat(last->key, last->valu);
		if (nhead == NULL)
		{
			nhead = nnode;
			tail = nnode;
		}
		else
		{
			tail->next = nnode;
			tail = nnode;
		}
		last = last->next;
	}
	return (nhead);
}

void	ft_lstclear(t_env **alist)
{
	t_env	*nlist;
	t_env	*clist;

	if (!alist)
		return ;
	nlist = *alist;
	while (nlist)
	{
		clist = nlist;
		free(clist);
		nlist = nlist->next;
	}
	*alist = NULL;
}

int	ft_lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
