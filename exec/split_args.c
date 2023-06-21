#include "Minishell.h"

// Function to split the line by the separator '|'
Node    *splitstring(char *line)
{
	Node *head = NULL;
	Node *tail = NULL;
	int len = strlen(line);
	if(!len)
		return (NULL);
	int i = 0;

	while (i < len)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			char quote = line[i];
			// i++;
			int j = i;
			while ((j + 1) < len && line[j + 1] != quote)
				j++;
			int substringlength = j - i + 1;
			char *substring = (char *)malloc((substringlength + 2) * sizeof(char));
			strncpy(substring, line + i, substringlength + 1);
			substring[substringlength + 1] = '\0';
			i = j + 2;

			Node *newnode = (Node *)malloc(sizeof(Node));
			newnode->data = substring;
			newnode->prev = NULL;
			newnode->next = NULL;

			if (tail == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				tail->next = newnode;
				newnode->prev = tail;
				tail = newnode;
			}
		}
		else if (line[i] == '|')
		{
			i++;

			Node *newnode = (Node *)malloc(sizeof(Node));
			newnode->data = NULL;
			newnode->prev = NULL;
			newnode->next = NULL;

			if (tail == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				tail->next = newnode;
				newnode->prev = tail;
				tail = newnode;
			}
		}
		else
		{
			int j = i;
			while (j < len && line[j] != '|' && line[j] != '\'' && line[j] != '\"')
				j++;
			int substringlength = j - i;
			char *substring = (char *)malloc((substringlength + 1) * sizeof(char));
			strncpy(substring, line + i, substringlength);
			substring[substringlength] = '\0';
			i = j;

			Node *newnode = (Node *)malloc(sizeof(Node));
			newnode->data = substring;
			newnode->prev = NULL;
			newnode->next = NULL;

			if (tail == NULL)
			{
				head = newnode;
				tail = newnode;
			}
			else
			{
				tail->next = newnode;
				newnode->prev = tail;
				tail = newnode;
			}
		}
	}

	return head;
}

// Function to free the doubly linked list memory
void freelist(Node *head)
{
	Node *current = head;
	while (current != NULL)
	{
		Node *temp = current;
		current = current->next;
		if(temp->data)
			free(temp->data);
		free(temp);
	}
}

// Function to print the doubly linked list
void printlist(Node *head)
 {
	Node *current = head;
	while (current != NULL)
	{

		if (current->data != NULL)
			printf("{%s}\n", current->data);
		else
			printf("(null)\n");
		current = current->next;
	}
}

