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

char *get_redfilen(int *i, int *j, char **cmd_l, char *which_red, t_env *env)
{
	char *file_name = NULL;
	char *true_face = NULL;
	int file_len = 0;
	int k;

	if(!strcmp(which_red, ">>") || !strcmp(which_red, "<<"))
		k = 2;
	else
		k = 1;
	if (cmd_l[*i][*j + k])
	{
		file_len = get_fl(&cmd_l[*i][*j + k]);
		file_name = strndup(&cmd_l[*i][*j + k], file_len);
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
	char *tmp = file_name;
	if (ft_strcmp(which_red ,"<<"))
	{
		true_face = removequotes(ft_expand(file_name, env));
		return (true_face);
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

void red_input(t_splitnode **node, int *i, int *j, char **cmdl, t_env *env)
{
	char *infile = get_redfilen(i, j, cmdl, "<", env);
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

void red_output(t_splitnode **node, int *i, int *j, char **cmdl, t_env *env)
{
	char *outfile = get_redfilen(i, j, cmdl, ">", env);
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
		char **cmdl = current->splitdata;
		int i = 0;
		if (cmdl)
		{
			while (cmdl[i] && !g_v.red_flag)
			{
				ft_memset(&cq, 0, sizeof(t_quote));
				int j = 0;
				while (cmdl[i][j] && !g_v.red_flag)
				{
					cq = check_quotes(cq,j, cmdl[i]);
					if (!cq.in_dquotes && !cq.in_squotes && !is_quote(cmdl[i][j]))
					{
						if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
							red_input(&current, &i, &j, cmdl, env);
						else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
							red_output(&current, &i, &j, cmdl, env);
						else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
							red_append(&current, &i, &j, cmdl, env);
					}
					if (cmdl[i][j])
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
