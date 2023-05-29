/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:42 by azarda            #+#    #+#             */
/*   Updated: 2023/05/22 19:57:27 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_env	*ft_lstnew(char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{

		new->key = key;
		new->valu = val;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*ptr;
	t_env	*head;

	if (alst)
	{
		if (*alst == NULL)
		{
			*alst = new;
			new = NULL;
		}
		else
		{
			head = *alst;
			ptr = *alst;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new;
			new->next = NULL;
		}
	}
}
