#include "Minishell.h"

int is_inside_quotes(char   *str) 
{
    int length = ft_strlen(str);
    int in_quotes = 0;
    int i = 0;

    while (i < length) 
    {
        if (str[i] == '"' || str[i] == '\'')
            in_quotes = !in_quotes;
        i++;
    }
    return in_quotes;
}

int count_words(char    *str) 
{
    int length = ft_strlen(str);
    int count = 0;
    int in_word = 0;
    int in_quotes = 0;
    int i = 0;

    while (i < length) 
    {
        if (str[i] == ' ' && !in_word && !in_quotes) 
        {
            i++;
            continue;
        }

        if (str[i] == '"' || str[i] == '\'')
            in_quotes = !in_quotes;
        else if (str[i] == ' ' && !in_quotes)
        {
            in_word = 0;
            count++;
        } else
            in_word = 1;
        i++;
    }

    if (in_word)
        count++;
    return count;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_string(char *str, int *word_count) {
    int length = ft_strlen(str);
    int count = 0;
    int in_word = 0;
    int in_quotes = 0;
    int i = 0;

    // Count the number of words
    while (i < length) {
        if ((str[i] == ' ' || str[i] == '\t') && !in_quotes) {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else if (str[i] == '"' || str[i] == '\'') {
            in_quotes = !in_quotes;
            in_word = 1;
        } else {
            in_word = 1;
        }

        i++;
    }

    if (in_word)
        count++;

    // Allocate memory for the words array
    char **words = (char **)calloc((count + 1) , sizeof(char *));
    int word_index = 0;
    int start_index = 0;
    in_word = 0;
    in_quotes = 0;
    i = 0;

    // Skip leading whitespace
    while (i < length && (str[i] == ' ' || str[i] == '\t'))
        i++;

    start_index = i;

    while (i <= length) {
        if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\0') && !in_quotes) {
            if (in_word) {
                words[word_index] = (char *)calloc((i - start_index + 1) , sizeof(char));
                strncpy(words[word_index], &str[start_index], i - start_index);
                words[word_index][i - start_index] = '\0';
                word_index++;
                in_word = 0;
            }
            start_index = i + 1;
        } else if (str[i] == '"' || str[i] == '\'') {
            in_quotes = !in_quotes;
            in_word = 1;
        } else {
            in_word = 1;
        }

        i++;
    }

    words[word_index] = NULL;
    *word_count = count;
    return words;
}



splitnode   *create_split_node(char   **splitdata, int word_count) 
{
    (void)  word_count;
    splitnode   *new_split_node = calloc(1, sizeof(splitnode));
    new_split_node->splitdata = splitdata;
    new_split_node->prev = NULL;
    new_split_node->next = NULL;
    new_split_node->in = -1;
    new_split_node->out = -1;
    return new_split_node;
}

splitnode   *splitdatalinkedlist(Node  *original_list) 
{
    splitnode   *head = NULL;
    splitnode   *tail = NULL;

    Node    *current = original_list;
    while (current != NULL) 
    {
        int word_count = 0;
        char    **splitdata = split_string(current->data, &word_count);
        splitnode   *new_node = create_split_node(splitdata, word_count);

        if (head == NULL) 
        {
            head = new_node;
            tail = head;
        } else 
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        current = current->next;
    }
    return head;
}

// void free_split_nodes(splitnode *head)
// {
//     while (head != NULL) 
//     {
//         splitnode   *current = head;
//         head = head->next;

//         int i = 0;
//         while (current->splitdata[i]) 
//         {
//             free(current->splitdata[i]);
//             i++;
//         }
//         free(current->splitdata);
//         free(current);
//     }
// }


