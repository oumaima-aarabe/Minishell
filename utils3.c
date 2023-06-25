#include "minishell.h"


int check_char(char c) 
{
    if (isalnum(c) || c == '_') {
        return 1;
    } else {
        return 0;
    }
}