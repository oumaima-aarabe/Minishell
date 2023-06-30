#include "minishell.h"

char **new_string(char **cmdl) {
    char **new_s;
    int i = 0;
    int j;
    int count = 0;
    bool print = false;
    int k = 0;
    int z;
    int wc = word_count(cmdl);

    new_s = (char **)malloc((wc + 1) * sizeof(char *));
    new_s[wc] = NULL;

    while (cmdl[i]) {
        j = 0;
        bool inside_quotes = false;

        while (cmdl[i][j]) {
            if (!inside_quotes && !is_quote(cmdl[i][j])) {
                if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<') {
                    if (cmdl[i][j + 1])
                        j += get_fl(&cmdl[i][j + 1]);
                    else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);
                } else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>') {
                    if (cmdl[i][j + 1])
                        j += get_fl(&cmdl[i][j + 1]);
                    else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);
                } else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>') {
                    if (cmdl[i][j + 2])
                        j += get_fl(&cmdl[i][j + 2]) + 1;
                    else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);
                } else if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<') {
                    later();
                } else {
                    print = true;
                    z = i;
                    count++;
                }
            }

            if (is_quote(cmdl[i][j]))
                inside_quotes = !inside_quotes;

            j++;
        }

        if (print) {
            new_s[k] = (char *)malloc(j + 1);
            strncpy(new_s[k], cmdl[z], j);
            new_s[k][j] = '\0';
            k++;
            print = false;
        }

        i++;
    }

    return new_s;
}