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






 0x7fbff8804490         0x7fbff8804550
 0x7fbff8804580         0x7fbff8804490
 0x7fbff88042d0         0x7fbff8804580
 0x7fbff88043e0         0x7fbff8804ab0
 0x7fbff88041c0         0x7fbff88041c0
 0x7fbff88041d0         0x7fbff88041d0
 0x7fbff8804540         0x7fbff88042d0
 0x7fbff8804550         0x7fbff88043e0
 0x7fbff8804ab0         0x7fbff8804540









