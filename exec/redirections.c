#include "Minishell.h"


bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	get_fl( char *str)
{
	int		length;
	t_quote cq;
	length = 0;

	ft_memset(&cq, 0, sizeof(t_quote));
	while (str[length] != '\0')
	{
		cq = check_quotes(cq, length, str);
		if (!cq.in_dquotes && !cq.in_squotes && (str[length] == '<' || str[length] == '>'))
			break; // Stop at red operator
		length++;
	}
	return length;
}

char *get_1redfilen(int *i, int *j, char **cmd_l, t_env *env)
{
	char *file_name = NULL;
	int file_len = 0;
	char *true_face = NULL;

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
		true_face = removequotes(ft_expand(file_name, env));
		return (true_face);
}
char *get_2redfilen(int *i, int *j, char **cmd_l, t_env *env)
{
	char *file_name = NULL;
	char *true_face = NULL;
	int file_len = 0;

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
		true_face = removequotes(ft_expand(file_name, env));
		return (true_face);
}

void red_append(t_splitnode **node, int *i, int *j, t_env *env)
{
	char *appfile = get_2redfilen(i, j, (*node)->splitdata, env);
	if (appfile)
	{
		int fd = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			if (!g_v.red_flag)
			{
				perror(appfile);
				g_v.red_flag = 1;
				(*node)->out = -2;
			}
		}
		else
		{
			if ((*node)->out != -1)
			close((*node)->out);
			(*node)->out = fd;
		}
		free(appfile);
	}
}

void red_input(t_splitnode **node, int *i, int *j, t_env *env)
{
	char *infile = get_1redfilen(i, j, (*node)->splitdata, env);
	if (infile)
	{
		int fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			if (!g_v.red_flag)
			{
				perror(infile);
				g_v.red_flag = 1;
				(*node)->in = -2;
			}
		}
		else
		{
			if ((*node)->in != -1)
			close((*node)->in);
			(*node)->in = fd;
		}
		free(infile);
	}
}

void red_output(t_splitnode **node, int *i, int *j, t_env *env)
{
	char *outfile = get_1redfilen(i, j, (*node)->splitdata, env);
	if (outfile)
	{
		int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			if (!g_v.red_flag)
            {
                perror(outfile);
                g_v.red_flag = 1;
                (*node)->out = -2;
            }
		}
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
	t_quote		cq;
	while (current != NULL)
	{
		g_v.red_flag = 0;
		int i = 0;
		if (current->splitdata)
		{
			while (current->splitdata[i] && !g_v.red_flag)
			{
				ft_memset(&cq, 0, sizeof(t_quote));
				int j = 0;
				while (current->splitdata[i][j] && !g_v.red_flag)
				{
					cq = check_quotes(cq,j, current->splitdata[i]);
					if (!cq.in_dquotes && !cq.in_squotes && !is_quote(current->splitdata[i][j]))
					{
						if (current->splitdata[i][j] == '<' && current->splitdata[i][j + 1] != '<')
							red_input(&current, &i, &j, env);
						else if (current->splitdata[i][j] == '>' && current->splitdata[i][j + 1] != '>')
							red_output(&current, &i, &j, env);
						else if (current->splitdata[i][j] == '>' && current->splitdata[i][j + 1] == '>')
							red_append(&current, &i, &j, env);
					}
					if (current->splitdata[i][j])
						j++;
				}
				i++;
		}
	}
		current = current->next;
	}
	trimmed = remove_redirections(node, 0);
	free_split_nodes(node);
	return trimmed;
}
