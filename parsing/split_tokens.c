#include "minishell.h"



#include <stdlib.h>
#include <string.h>

int count_tokens(char *data) 
{
    int len = strlen(data);
    int i = 0;
    int counttokens = 0;
    int tokenlength = 0;

    while (i < len)
    {
        if (data[i] == '\'' || data[i] == '\"') 
        {
            char quote = data[i];
            i++;
            while (i < len && data[i] != quote)
                i++;
            counttokens++;
        }
        if (data[i] == ' ') 
        {
            if (tokenlength > 0)
            {
                counttokens++;
                tokenlength = 0;
            }
        }
        else
            tokenlength++;
        i++;
    }
    if (tokenlength > 0)
        counttokens++;
    return counttokens;
}

char **split_tokens(char *data, int counttokens) 
{
    int len = strlen(data);
    int i = 0;
    int tokenindex = 0;
    int tokenlength = 0;
    char *token = NULL;
    char **splitdata = ft_calloc((counttokens + 1), sizeof(char *));
    
while (i < len) 
{
    if (data[i] == '\'' || data[i] == '\"') 
    {
        char quote = data[i];
        tokenlength++;
        token = ft_calloc((tokenlength + 1), sizeof(char));
        token[tokenlength - 1] = data[i];
        i++;
        while (i < len && data[i] != quote) 
        {
            tokenlength++;
            char* new_token = ft_calloc((tokenlength + 1), sizeof(char));
            memcpy(new_token, token, tokenlength - 1);
            new_token[tokenlength - 1] = data[i];
            free(token);
            token = new_token;
            i++;
        }
    }
    if (data[i] == ' ' || data[i] == '\t') 
    {
        if (tokenlength > 0)
        {
            token[tokenlength] = '\0';
            splitdata[tokenindex] = token;
            tokenindex++;
            tokenlength = 0;
            token = NULL;
        }
    }
    else 
    {
        tokenlength++;
        char* new_token = ft_calloc((tokenlength + 1), sizeof(char));
        memcpy(new_token, token, tokenlength - 1);
        new_token[tokenlength - 1] = data[i];
        free(token);
        token = new_token;
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

splitnode *createsplitnode(char **splitdata) 
{
    splitnode *newnode = (splitnode *)malloc(sizeof(splitnode));
    // if (splitdata == NULL)
    //     return NULL;

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

void free_splitnode(splitnode *node)
{
    if (node == NULL)
        return;

    char **splitdata = node->splitdata;
    if (splitdata != NULL)
    {
        int i = 0;
        while (splitdata[i] != NULL)
        {
            free(splitdata[i]);
            i++;
        }
        free(splitdata);
    }

    free(node);
}

splitnode *splitdataLinkedList(Node *originalList) 
{
    splitnode *head = NULL;
    splitnode *tail = NULL;
    Node *current = originalList;
    char **splitdata = NULL;
    
    while (current != NULL) 
    {
        if (current->data == NULL) 
        {
            if (current->next)
                current = current->next;
            else
                return head;
        }
        
        char *data = current->data;
        int counttokens = count_tokens(data);
        splitdata = split_tokens(data, counttokens);
        splitnode *newnode = createsplitnode(splitdata);
        
        if (newnode == NULL)
             free_splitnode(newnode);
        else 
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
