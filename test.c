/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:33:55 by azarda            #+#    #+#             */
/*   Updated: 2023/05/21 15:45:52 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
# include <unistd.h>


#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char **envp)
{
    int pid = fork();
    char *p[2] = {"bash"};
    if (pid == 0)
        execve("/bin/bash", p, envp);
    wait(NULL);
}
