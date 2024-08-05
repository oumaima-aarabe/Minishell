/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:39:54 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 06:25:12 by ouaarabe         ###   ########.fr       */
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

void	ft_free_plus(char *s1, char *s2, void *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

void	ft_remov_lis(char *cmd)
{
	t_env	*tmp_env;
	t_env	*prev;

	tmp_env = g_v.env;
	prev = NULL;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, cmd))
		{
			if (!prev)
			{
				prev = tmp_env->next;
				g_v.env = prev;
				ft_free_plus(tmp_env->key, tmp_env->valu, tmp_env);
			}
			else
			{
				prev->next = tmp_env->next;
				ft_free_plus(tmp_env->key, tmp_env->valu, tmp_env);
			}
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
}
