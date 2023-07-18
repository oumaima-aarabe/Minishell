/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:19:19 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 07:36:07 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	**splitget(int hr, t_splitnode *current)
{
	int		wc;
	char	**splitdata;

	splitdata = NULL;
	if (hr == 0)
	{
		if (current->in == -2 || current->out == -2)
			wc = 0;
		else
			wc = word_count(current->splitdata);
		if (wc)
			splitdata = newstring(current->splitdata, wc);
	}
	else if (hr == 1)
	{
		if (g_v.sig_flag)
			wc = 0;
		else
			wc = wc_heredoc(current->splitdata);
		if (wc)
			splitdata = ns_heredoc(current->splitdata, wc);
	}
	return (splitdata);
}

t_splitnode	*remove_redirections(t_splitnode  *node, int hr)
{
	t_splitnode	*cr;
	t_splitnode	*head;
	t_splitnode	*tail;

	cr = node;
	head = NULL;
	tail = NULL;
	while (cr != NULL)
	{
		if (head == NULL)
		{
			head = create_new_node(splitget(hr, cr), cr->in, cr->out);
			tail = head;
			if (g_v.sig_flag)
				return (g_v.sig_flag = 0, head);
		}
		else
		{
			tail->next = create_new_node(splitget(hr, cr), cr->in, cr->out);
			(tail->next)->prev = tail;
			tail = tail->next;
		}
		cr = cr->next;
	}
	return (head);
}
/////////////////////////////////////////////////////////

t_splitnode	*create_new_node(char **splitdata, int in, int out)
{
	t_splitnode   *new_split_node = calloc(1, sizeof(t_splitnode)); // ! hana tani 3la calooc bla protect
	new_split_node->splitdata = splitdata;
	new_split_node->prev = NULL;
	new_split_node->next = NULL;
	new_split_node->in = in;
	new_split_node->out = out;
	return (new_split_node);
}

/////////////////////////////////////////////////////////

t_quote	skip_red(t_quote cq, char **cmdl)
{
	if (!cq.ind && !cq.ins && !is_quote(cmdl[cq.i][cq.j]))
	{
		if ((cmdl[cq.i][cq.j] == '<' && cmdl[cq.i][cq.j + 1] != '<') \
		|| (cmdl[cq.i][cq.j] == '>' && cmdl[cq.i][cq.j + 1] != '>'))
		{
			if (cmdl[cq.i][cq.j + 1])
			cq.j +=   get_fl(&cmdl[cq.i][cq.j + 1]) + 1;
			else if (cmdl[cq.i + 1])
			cq.j = get_fl(cmdl[++(cq.i)]);
			return (cq);
		}
		else if (cmdl[cq.i][cq.j] == '>' && cmdl[cq.i][cq.j + 1] == '>')
		{
			if (cmdl[cq.i][cq.j + 2])
			cq.j +=   get_fl(&cmdl[cq.i][cq.j + 2]) + 2;
			else if (cmdl[cq.i + 1])
			cq.j = get_fl(cmdl[++(cq.i)]);
			return (cq);
		}
	}
	if (cmdl[cq.i][cq.j])
		cq.j++;
	return (cq);
}

int	word_count(char **cmdl)
{
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	if (cmdl)
	{
		while (cmdl[cq.i])
		{
			cq.j = 0;
			while (cmdl[cq.i][cq.j])
			{
				cq = check_quotes(cq, cq.j, cmdl[cq.i]);
				if ((cq.ind || cq.ins) ||!is_redirection(cmdl[cq.i][cq.j]))
					cq.print = true;
				cq = skip_red(cq, cmdl);
			}
			if (cq.print)
			{
				cq.wc++;
				cq.print = false;
			}
			cq.i++;
		}
	}
	return (cq.wc);
}
