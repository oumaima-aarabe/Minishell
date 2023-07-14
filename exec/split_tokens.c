#include "Minishell.h"

int count_words(char    *str) 
{
	int count = 0;
	int in_word = 0;
	int i = 0;
	t_quote cq;

	memset(&cq, 0, sizeof(t_quote));
	while (i < ft_strlen(str)) 
	{
		cq = check_quotes(cq, i, str);
		if (str[i] == ' ' && !in_word && !cq.in_dquotes && !cq.in_squotes) 
		{
			i++;
			continue;
		}
		if (str[i] == ' ' && !cq.in_dquotes && !cq.in_squotes)
		{
			in_word = 0;
			count++;
		}
		else
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return count;
}

char **split_string(char *str, int *word_count) {
	int length = ft_strlen(str);
	int count = 0;
	int in_word = 0;
	int i = 0;
	t_quote cq;

	memset(&cq, 0, sizeof(t_quote));
	while (i < length) 
	{
		cq = check_quotes(cq, i, str);
		if ((str[i] == ' ' || str[i] == '\t') && !!cq.in_dquotes && !cq.in_squotes) 
		{
			if (in_word) 
			{
				count++;
				in_word = 0;
			}
		}
		else 
			in_word = 1;
		i++;
	}

	if (in_word)
		count++;
	char **words = (char **)calloc((count + 1) , sizeof(char *));
	int word_index = 0;
	int start_index = 0;
	in_word = 0;
	i = 0;

	cq = check_quotes(cq, i, str);
	// Skip leading whitespace
	while (i < length && (str[i] == ' ' || str[i] == '\t'))
		i++;

	start_index = i;

	while (i <= length) 
	{
		cq = check_quotes(cq, i, str);
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '\0') && !cq.in_dquotes && !cq.in_squotes) 
		{
			if (in_word) {
				words[word_index] = (char *)calloc((i - start_index + 1) , sizeof(char));
				strncpy(words[word_index], &str[start_index], i - start_index);
				words[word_index][i - start_index] = '\0';
				word_index++;
				in_word = 0;
			}
			start_index = i + 1;
		}
		 else
			in_word = 1;
		i++;
	}

	words[word_index] = NULL;
	*word_count = count;
	return words;
}



t_splitnode   *create_split_node(char   **splitdata, int word_count) 
{
	(void)  word_count;
	t_splitnode   *new_split_node = calloc(1, sizeof(t_splitnode));
	new_split_node->splitdata = splitdata;
	new_split_node->prev = NULL;
	new_split_node->next = NULL;
	new_split_node->in = -1;
	new_split_node->out = -1;
	return new_split_node;
}

t_splitnode   *splitdatalinkedlist(t_Node  *original_list) 
{
	t_splitnode   *head = NULL;
	t_splitnode   *tail = NULL;

	t_Node    *current = original_list;
	while (current != NULL) 
	{
		int word_count = 0;
		char    **splitdata = split_string(current->data, &word_count);
		t_splitnode   *new_node = create_split_node(splitdata, word_count);

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
