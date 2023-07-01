#include "Minishell.h"

t_gs	g_v;

// int which_quotes(char c) 
// {
// 	if (c == '\'')
// 		return 1;
// 	else if (c == '\"')
// 		return 2;
// 	return 0;
// }

// char  **checkquotes(char **splitdata, t_env *en)
// {
// 	char **new2_0 = NULL;
// 	int start_index;
// 	int i;
// 	int j;
	
// 	i = 0;
// 	while (splitdata[i]) 
// 	{
// 		j = 0;
// 		while(splitdata[i][j])
// 		{
			
// 			int quoteType = which_quotes(splitdata[i][j]);

// 			if (quoteType == 1)
// 			{
// 				start_index = ++j;
// 				while (splitdata[i][j] && quoteType != which_quotes(splitdata[i][j]))
// 					j++;
				
// 			}
// 			else if (quoteType == 2)
// 			{
// 				start_index = j;
// 				while(splitdata[i][j] && quoteType != which_quotes(splitdata[i][j]))
// 					j++;
// 			}
// 			if (splitdata[i][j])
// 				j++;
// 		}
// 		i++;
// 	}
// 	return (new2_0);
// }


char *removequotes(char *input)
{
	int length = strlen(input);
	int count = 0;
	int insinglequotes = 0;
	int indoublequotes = 0;

	// Count the number of characters without quotes
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

	// Copy characters without quotes to the output array
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
	return output;
}

// int main()
// {
// 	char input[] = "Hello 'World'! \"How are you?\"";
// 	char *result = removequotes(input);
// 	printf("Result: %s\n", result);
// 	free(result);

// 	return 0;
// }

