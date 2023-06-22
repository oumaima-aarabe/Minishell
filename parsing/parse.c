#include "minishell.h"

void parsing(char* prompt) 
{
    Node* node = splitstring(prompt);
    splitnode* tokens = splitdatalinkedlist(node);
    freenodes(node);

//    tokens = handle_redirections(tokens);
    splitnode *current = tokens;
    while (current != NULL) 
    {
        splitnode* next = current->next;

        // Print the split data
        int i = 0;
        while (current->splitdata[i]) 
        {
            printf("Token %d: %s\n", i + 1, current->splitdata[i]);
            i++;
        }

        // Free the split data
        i = 0;
        while (current->splitdata[i] != NULL) 
        {
            free(current->splitdata[i]);
            i++;
        }
        free(current->splitdata);

        free(current);

        current = next;
    }
}