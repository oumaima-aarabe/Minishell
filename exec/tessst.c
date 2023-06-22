
int phandle(int status)
{
    int neew_statis = WTERMSIG(status);

    if ( == SIGINT)
        printf("Minishell : SIG : %s\n", "interrupt");

SIGQUIT "quit";
SIGILL  "illegal instruction (not reset when caught)";
SIGTRAP "trace trap (not reset when caught)";
SIGABRT "abort()";
SIGEMT  "EMT instruction";
SIGFPE  "floating point exception";
SIGKILL "kill (cannot be caught or ignored)";
SIGBUS  "bus error";
SIGSEGV "segmentation violation";
SIGSYS  "bad argument to system call";
SIGPIPE "write on a pipe with no one to read it";
SIGALRM "alarm clock";
SIGTERM "software termination signal from kill";
SIGURG  "urgent condition on IO channel";
SIGSTOP "sendable stop signal not from tty";

    return (WTERMSIG(status) + 128);
}

int    extract_status(int status)
{
    if (WEXITED(status))
        return (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        return (phandle(status));
}



int main()
{
    pid_t pid = fork();
    wait(&status)

    exit_status = extract_status(status);
}
