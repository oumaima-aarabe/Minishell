#include "Minishell.h"

t_gs	g_v;

bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}


int	get_fl(const char *str)
{
	int		length;
	bool	inside_quotes;
	char	quote_type;

	length = 0;
	inside_quotes = false;
	quote_type = '\0';
	while (str[length] != '\0')
	{

		if (str[length] == '\'' || str[length] == '\"')
		{
			if (inside_quotes && quote_type == str[length])
			{
				inside_quotes = false;
				quote_type = '\0';
			}
			else if (!inside_quotes)
			{
				inside_quotes = true;
				quote_type = str[length];
			}
		}
		else if (!inside_quotes && (str[length] == '<' || str[length] == '>'))
			break; // Stop at red operator

		length++;
	}
	return length;
}
char *get_redfilen(int *i, int *j, char **cmd_l, char *which_red, t_env *env)
{
	char *file_name = NULL;
	char *true_face = NULL;
	int file_len = 0;

	if (!strcmp(which_red, ">>") || !strcmp(which_red, "<<"))
	{
		if (cmd_l[*i][*j + 2])
		{
			file_len = get_fl(&cmd_l[*i][*j + 2]);
			file_name = strndup(&cmd_l[*i][*j + 2], file_len);
			*j += file_len;
		}
		else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
		{
			*j = 0;
			file_len = get_fl(cmd_l[*i + 1]);
			file_name = strndup(cmd_l[*i + 1], file_len);
			*i += 1;
			*j += file_len;
		}
	}
	else if (strcmp(which_red, ">") == 0)
	{
		if (cmd_l[*i][*j + 1])
		{
			file_len = get_fl(&cmd_l[*i][*j + 1]);
			file_name = strndup(&cmd_l[*i][*j + 1], file_len);
			*j += file_len;
		}
		 else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
		 {
			 *j = 0;
			file_len = get_fl(cmd_l[*i + 1]);
			file_name = strndup(cmd_l[*i + 1], file_len);
			*i += 1;
			*j += file_len;
		}
	}
	 else if (strcmp(which_red, "<") == 0)
	 {
		if (cmd_l[*i][*j + 1])
		{
			file_len = get_fl(&cmd_l[*i][*j + 1]);
			file_name = strndup(&cmd_l[*i][*j + 1], file_len);
			*j += file_len;
		}
		else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
		{
			 *j = 0;
			file_len = get_fl(cmd_l[*i + 1]);
			file_name = strndup(cmd_l[*i + 1], file_len);
			*i += 1;
			*j += file_len;
		}
	}
	char *tmp = file_name;
	if (ft_strcmp(which_red ,"<<"))
	{

		true_face = removequotes(ft_expand(file_name, env));
		return true_face;
	}
	else
		return (tmp);
}

void red_append(t_splitnode **node, int *i, int *j, char **cmdl, t_env *env)
{
	char *appfile = get_redfilen(i, j, cmdl, ">>", env);
	if (appfile)
	{
		int fd = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			perror(appfile);
		else
		{
			if ((*node)->out != -1)
				close((*node)->out);
			(*node)->out = fd;
		}
		free(appfile);
	}
}

void red_input(t_splitnode **node, int *i, int *j, char **cmdl, t_env *env)
{
	char *infile = get_redfilen(i, j, cmdl, "<", env);
	if (infile)
	{
		int fd = open(infile, O_RDONLY);
		if (fd == -1)
			perror(infile);
		else
		{
			if ((*node)->in != -1)
				close((*node)->in);
			(*node)->in = fd;
		}
		free(infile);
	}
}

void red_output(t_splitnode **node, int *i, int *j, char **cmdl, t_env *env)
{
	char *outfile = get_redfilen(i, j, cmdl, ">", env);
	if (outfile)
	{
		int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			perror(outfile);
		else
		{
			if ((*node)->out != -1)
				close((*node)->out);
			(*node)->out = fd;
		}
		free(outfile);
	}
}

t_splitnode *handle_redirections(t_splitnode *node, t_env *env)
{
	t_splitnode *current = node;
	t_splitnode *trimmed;
	while (current != NULL)
	{
		char **cmdl = current->splitdata;
		int i = 0;

		while (cmdl[i])
		{
			int j = 0;
			bool inside_quotes = false;

			while (cmdl[i][j])
			{
				if (!inside_quotes && !is_quote(cmdl[i][j]))
				{
					if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
						red_input(&current, &i, &j, cmdl, env);
					else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
						red_output(&current, &i, &j, cmdl, env);
					else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
						red_append(&current, &i, &j, cmdl, env);
				}
				if (is_quote(cmdl[i][j]))
					inside_quotes = !inside_quotes;

				if (cmdl[i][j])
					j++;
			}
			i++;
		}
		current = current->next;
	}
	trimmed = remove_redirections(node, 0);
	free_split_nodes(node);
	return trimmed;
}
