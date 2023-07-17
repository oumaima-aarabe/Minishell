








//!strndup

/////////////////////////////////////////
s
Minishell ls: No such file or directory
Minishell -> pwd
/Users/azarda/Desktop/Minishell/exec
Minishell -> echo

Minishell -> ls -la
Minishell ls: No such file or directory
Minishell -> $?
Minishell 2: No such file or directory
Minishell ->
///////////////////////////////




//!/////////////////////////////////////////
Minishell -> unset PWD
Minishell -> cd ..
Minishell : cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
Minishell -> PWD
PWD: .: No such file or directory
Minishell -> pwd
/Users/azarda/Desktop/Minishell/exec/a/b/c/d/e
Minishell -> ls
Minishell -> cd
Minishell -> pwd
/Users/azarda
Minishell -> cd .
Minishell -> pwd
/Users/azarda
Minishell -> cd -
/Users/azarda
//!1 (1.00K) ROOT LEAK: 0x7fbb2c008600 [1024]  length: 13  "/Users/azarda"
//!old pwd




Minishell -> export l3bid="oumaima zerda"
Minishell: l3bid=oumaima zerda : not a valid identifier
Minishell -> echo $l3bid
3bid

Minishell -> export $l3bid=$l3bid
Minishell: 3bid=3bid : not a valid identifier
Minishell ->

