/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/06/07 17:47:40 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void  ctr_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line(" ", 0);
	rl_redisplay();

}

//________________________________________________________________________________

void le()
{
	system("leaks Minishell");
}
//________________________________________________________________________________

t_env *ft_creat(char *key, char *val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	else
	{
		new->key =  key;
		new->valu = val;
		new->next = NULL;
	}
	return (new);
}

//________________________________________________________________________________

t_env *environment(char **env)
{
	int i = 0;

	t_env *en = NULL;
	char **tmp;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		ft_lstadd_back(&en, ft_creat(ft_strdup(tmp[0]) ,ft_strdup(tmp[1])));
		ft_free_(tmp);
		tmp = NULL;
		i++;
	}
	return(en);
}

//________________________________linked_list________________________________________________


t_env *duplicate_linked_list(t_env *last)
{
    t_env *nhead = NULL;
    t_env *tail = NULL;
	t_env *nnode = NULL;


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

    return nhead;
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


//________________________________________________________________________________

void ft_env(t_env *env)
{
	while(env )
	{
		if(env->valu)
		printf("%s=%s\n", env->key, env->valu);
		env = env->next;
	}
}

//________________________________________________________________________________


int compar(int a, int b)
{
	if(a > b)
		return (0);
	return(1);
}

//________________________________________________________________________________

int ft_egal(char *st)
{
	int i = 0;

	while(st[i])
	{
		if(st[i] == '=')
		return (i);
		i++;
	}
	return 0;
}

//________________________________________________________________________________

void ft_export(t_env *env, char **cmd)
{
	char 	*swap;

	t_env *tmp;
	t_env *tmp1;
	int i;

	if(cmd[1])
	{
		if(ft_egal(cmd[1]))
		{
			i = ft_egal(cmd[1]);
			ft_lstadd_back(&env,ft_creat(ft_substr(cmd[1], 0, i), ft_substr(cmd[1], i + 1, ft_strlen(cmd[1]) - i)));
		}
		else
			ft_lstadd_back(&env, ft_creat(ft_strdup(cmd[1]), NULL));
		return ;
	}
	tmp = duplicate_linked_list(env);

	tmp1 = tmp;
	while(tmp->next != NULL)
	{
		if ((compar(tmp->key[0], tmp->next->key[0])) == 0)
		{
			swap = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = swap;
			swap = tmp->valu;
			tmp->valu = tmp->next->valu;
			tmp->next->valu = swap;
			tmp = tmp1;
		}
		else
			tmp = tmp->next;
	}
	tmp = tmp1;
	while(tmp)
	{
		if(tmp->valu)
		printf("declare -x %s=\"%s\"\n",tmp->key, tmp->valu);
		else
		printf("declare -x %s\n",tmp->key);
		tmp = tmp->next;
	}
	ft_lstclear(&tmp1);
}

//________________________________________________________________________________

// void ft_unset(t_env *env, char **cmd)
// {

// }

//________________________________________________________________________________


//________________________________________________________________________________
//________________________________________________________________________________


int main(int ac, char **av, char  **env)
{
	(void)av;
	// char *pwd;
	char *str;
	char **ok;
	t_env *en;
	en = environment(env);
	if(ac != 1)
	{
		printf("Minishell no take arguments\n"); // change msg
		exit(1);
	}



	while(1337)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT,  ctr_c);
		//pwd = ft_strjoin(getcwd(NULL, 0), " -> "); // 1bite leaks pwd
		str = readline("minishell $ ");
		// free(pwd);
		if(!str)
		{
			printf("exit\n");
			// atexit(le);
			exit(0);
		}
		ok = ft_split(str, ' ');
		add_history(str);
		free(str);
		str = NULL;
		if(!(ft_strcmp(ok[0], "env")))
			ft_env(en); // he nide SHELV
		else if(!(ft_strcmp(ok[0], "export")))
			ft_export(en, ok);
		// else if(!(ft_strcmp(ok[0], "unset")))
		// 	ft_unset(en, ok);
		else
			ft_exec(ok, en, env);
		ft_free_(ok);
		ok = NULL;
	}
}
