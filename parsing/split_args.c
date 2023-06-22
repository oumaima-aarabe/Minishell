#include "minishell.h"

Node* createnode(char* data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

int check_for_quotes(char* line, int index)
{
    int inquotes = 0;
    int i = 0;

    while (i < index) {
        if (line[i] == '"' || line[i] == '\'')
            inquotes = !inquotes;
        i++;
    }

    return !inquotes;
}

Node* splitstring(char* line) 
{
    Node* head = NULL;
    Node* tail = NULL;
    int length = strlen(line);
    int i = 0;
    int start = 0;

    while (i < length) 
    {
        if (line[i] == '|' && check_for_quotes(line, i)) 
        {
            line[i] = '\0';
            if (head == NULL) 
            {
                head = createnode(&line[start]);
                tail = head;
            } 
            else 
            {
                tail->next = createnode(&line[start]);
                tail->next->prev = tail;
                tail = tail->next;
            }
            start = i + 1;
        }
        i++;
    }
    if (head == NULL) 
    {
        head = createnode(line);
        tail = head;
    } 
    else 
    {
        tail->next = createnode(&line[start]);
        tail->next->prev = tail;
        tail = tail->next;
    }

    return head;
}

void freenodes(Node* head) 
{
    while (head != NULL) 
    {
        Node* current = head;
        head = head->next;
        free(current->data);
        free(current);
    }
}
			