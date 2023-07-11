/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:39:54 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/11 11:03:03 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_free_(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	freenodes(t_Node *head)
{
	t_Node	*current;

	current = head;
	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current->data);
		free(current);
	}
}

void	free_split_nodes(t_splitnode *head)
{
	int			i;
	t_splitnode	*current;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		i = 0;
		if (current->splitdata)
		{
			while (current->splitdata[i])
			{
				free(current->splitdata[i]);
				i++;
			}
		}
		free(current->splitdata);
		free(current);
	}
}
