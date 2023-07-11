#include "Minishell.h"


char *removequotes(char *input)
{
	if (input)
	{

	int length = strlen(input);
	int count = 0;
	int insinglequotes = 0;
	int indoublequotes = 0;

	int i = 0;
	while (i < length)
	{
		if (input[i] == '\'' && !indoublequotes)
			insinglequotes = !insinglequotes;
		else if (input[i] == '"' && !insinglequotes)
			indoublequotes = !indoublequotes;
		else
			count++;
		i++;
	}

	char *output = calloc(count + 1, sizeof(char));

	int j = 0;
	insinglequotes = 0;
	indoublequotes = 0;

	i = 0;
	while (i < length)
	{
		if (input[i] == '\'' && !indoublequotes)
			insinglequotes = !insinglequotes;
		else if (input[i] == '"' && !insinglequotes)
			indoublequotes = !indoublequotes;
		else
		{
			output[j] = input[i];
			j++;
		}
		i++;
	}
	free (input);
	return output;
	}
	return input;
}
