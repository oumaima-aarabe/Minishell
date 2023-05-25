#include "Minishell.h"

void    




int main(int argc, char **argv, char **env)
{
    char *pwd;
    char *prompt;

   pwd = ft_strjoin(getcwd(NULL, 0), " -> ");
   prompt = readline(pwd);
   free(pwd);

}