#include "minishell.h"




int counttokens(char *data) 
{
    int len = strlen(data);
    int i = 0;
    int countcokens = 0;
    int tokenlength = 0;

    while (i < len)
     {
        // if (data[i] == '\'' || data[i] == '\"') 
        // {
        //     char quote = data[i];
        //     i++;
        //     while (i < len && data[i] != quote)
        //         i++;
        // }
        if (data[i] == ' ') 
        {
            if (tokenlength > 0)
            {
                countcokens++;
                tokenlength = 0;
            }
        }
        else
            tokenlength++;
        i++;
    }
    if (tokenlength > 0)
        countcokens++;
    return countcokens;
}

char    **splittokens(char *data, int countcokens) 
{
    int len = strlen(data);
    int i = 0;
    int tokenindex = 0;
    int tokenlength = 0;
    char *token = (char *)calloc((tokenlength + 1) ,sizeof(char));
    char **splitdata = (char **)calloc((countcokens + 1) , sizeof(char *));
    
    while (i < len) 
    {
        // if (data[i] == '\'' || data[i] == '\"') 
        // {
        //     char quote = data[i];
        //     i++;
        //     while (i < len && data[i] != quote) 
        //     {
        //         tokenlength++;
        //         token = (char *)realloc(token, (tokenlength + 1) * sizeof(char));
        //         token[tokenlength - 1] = data[i];
        //         i++;
        //     }
        // }
        if (data[i] == ' ' || data[i] == '\t') 
        {
            if (tokenlength > 0)
             {
                token[tokenlength] = '\0';
                splitdata[tokenindex] = token;
                tokenindex++;
                tokenlength = 0;
                token = (char *)calloc((tokenlength + 1) , sizeof(char));
            }
        }
        else 
        {
            tokenlength++;
            token = (char *)realloc(token, (tokenlength + 1) * sizeof(char));
            token[tokenlength - 1] = data[i];
        }
        i++;
    }
    
    if (tokenlength > 0) 
    {
        token[tokenlength] = '\0';
        splitdata[tokenindex] = token;
    }
    else
        splitdata[tokenindex] = NULL;
    
    return splitdata;
}

splitnode   *createsplitnode(char **splitdata) 
{
    splitnode *newnode = (splitnode *)malloc(sizeof(splitnode));
    newnode->splitdata = splitdata;
    newnode->prev = NULL;
    newnode->next = NULL;
    
    return newnode;
}

void addToSplitList(splitnode **head, splitnode **tail, splitnode *newnode) 
{
    if (*tail == NULL) 
    {
        *head = newnode;
        *tail = newnode;
    }
    else 
    {
        (*tail)->next = newnode;
        newnode->prev = *tail;
        *tail = newnode;
    }
}

splitnode   *splitdataLinkedList(Node *originalList) 
{
    splitnode *head = NULL;
    splitnode *tail = NULL;
    Node *current = originalList;
    
    while (current != NULL) 
    {
        if (current->data == NULL) {

            if (current->next)
                current = current->next;
            else
                return head;
        }
        
        char *data = current->data;
        int countcokens = counttokens(data);
        char **splitdata = splittokens(data, countcokens);
        splitnode *newnode = createsplitnode(splitdata);
        addToSplitList(&head, &tail, newnode);
        
        current = current->next;
    }
    
    return head;
}


// int main() {

//     Node *head = splitString("ls -la | cut -ghj | oumiooo");
//     splitnode *splitList = splitdataLinkedList(head);
    

//     splitnode *current = splitList;
//     while (current != NULL) {
//         char **splitdata = current->splitdata;
        
//         // Print the split data
//         int i = 0;
//         while (splitdata[i] != NULL) {
//             printf("Token %d: %s\n", i + 1, splitdata[i]);
//             i++;
//         }
        
//         // Free the memory allocated for split data
//         i = 0;
//         while (splitdata[i] != NULL) {
//             free(splitdata[i]);
//             i++;
//         }
//         free(splitdata);
        
//         current = current->next;
//     }
    
// }
