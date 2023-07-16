env -i ./minishell

/****************************************************************/
Minishell -> unset PATH
Minishell -> ls
minishell   exeve faill   :: No such file or directory
Minishell -> clear
minishell   exeve faill   :: No such file or directory
/****************************************************************/

/****************************************************************/

//! mkdir -p a/b/c/d and trying to go back after removing this dirs

Minishell -> pwd
/Users/ouaarabe/Desktop/merged/exec/a/b/c/d
Minishell -> cd ../../../../../../..
minishell: cd: ../../../../../../..: No such file or directory
Minishell -> pwd
/Users/ouaarabe/Desktop/merged/exec/a/b/c/d
Minishell -> cd ../../../../../../..
minishell: cd: ../../../../../../..: No such file or directory
//! 1 (48 bytes) ROOT LEAK: 0x7ff294904500 [48]  length: 43  "/Users/ouaarabe/Desktop/merged/exec/a/b/c/d"
//! this leak apear when the path ofgoing back (../../../../../../..) is larger than the real path (a/b/c/d)
/****************************************************************/

/****************************************************************/
Minishell -> .
minishell   exeve faill   :: Permission denied
Minishell -> ..
minishell   exeve faill   :: Permission denied
Minishell -> 
/****************************************************************/

//!heredoc quotes

