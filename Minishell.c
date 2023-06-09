/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 17:11:41 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void  ctr_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line(" ", 0);
	rl_redisplay();

}

//________________________________________________________________________________

void le()
{
	system("leaks Minishell");
}
//________________________________________________________________________________



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




void deleteNode(t_env **head, char *key)
 {
    t_env *current = *head;
    t_env *previous = NULL;

    // Vérifier si la valeur à supprimer correspond au premier nœud
    if (current != NULL && current->key == key)
	{
        *head = current->next; // Réattribuer la tête de liste
        free(current);
        return;
    }

    // Parcourir la liste jusqu'à trouver le nœud à supprimer
    while (current != NULL && current->key != key)
	{
        previous = current;
        current = current->next;
    }

    // Réattribuer les pointeurs pour contourner le nœud à supprimer
    previous->next = current->next;
	// puts("herr");
    free(current); // Libérer la mémoire
}



//________________________________________________________________________________



//________________________________________________________________________________

char *ft_take_key(char *str, t_env *env)
{

	str++;
	while(env)
	{
		if(!ft_strcmp(str, env->key))
		return (env->valu);
		env = env->next;
	}
	return NULL;
}

char **ft_expend(char **cmd, t_env *en)
{
	int i = 0;
	int j = 0;

	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			if(cmd[i][j] ==  '$')
			{
				cmd[i] = ft_strdup(ft_take_key(cmd[i], en));
				// if(!cmd[i])
					// cmd[i] = ft_strdup("");
			}
			j++;
		}
		i++;
	}
	// i = 0;
	// j = 0;
	// while(cmd[i])
	// {
	// 	printf("--->>>%s\n", cmd[i]);
	// 	i++;
	// }
	return (cmd);
}

//________________________________________________________________________________
//________________________________________________________________________________


int main(int ac, char **av, char  **env)
{
	(void)av;
	// char *pwd;
	char *str;
	char **cmd;
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
		cmd = ft_split(str, ' ');
		cmd = ft_expend(cmd,en);
		add_history(str);
		free(str);
		str = NULL;
		if(ft_execut_bultins(cmd, en))
			continue;
		else
			ft_exec(cmd, en, env);
		ft_free_(cmd);
		cmd = NULL;
	}
}
