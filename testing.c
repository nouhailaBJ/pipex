# include "pipex.h"


void	ft_stock_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_data.envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		g_data.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_data.envp[i] = NULL;
}

void error_file(char *file)
{
	ft_putstr_fd("pipex: ", 1);
		perror(file);
	g_ret = 1;
}

void	stock_args(char **av, char **envp)
{
	ft_stock_env(envp);
	g_data.file1 = av[1];
	g_data.file2 = av[4];
	g_data.s1 = ft_split(av[2], ' ');
	g_data.s2 = ft_split(av[3], ' ');
	g_data.inp = open(av[1], O_RDONLY);
	if (g_data.inp < 0)
		error_file(av[1]);
	g_data.out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (g_data.out < 0)
		error_file(av[4]);
}

void ft_error(char *msg)
{
	ft_putstr_fd(msg, 1);
	g_ret = 127;
}
int 	ft_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_ret = 127;
	return (0);
}

int check_errors()
{
	if (!g_data.s1[0])
		ft_putstr_fd("pipex: : command not found\n", 1);
	if (g_data.s1[0] && search_path(g_data.s1[0], 1) == 0)
		ft_not_found(g_data.s1[0]);
	if (g_data.s2[0] && search_path(g_data.s2[0], 2) == 0)
		ft_not_found(g_data.s2[0]);
	else if (g_data.s2[0] && search_path(g_data.s2[0], 2))
		g_ret = 0;
	if (!g_data.s2[0])
		ft_error("pipex: : command not found\n");
	return (1);
}
int main(int ac, char **av, char **envp)
{
	g_ret = 0;
	if (ac == 5)
	{
		stock_args(av, envp);
		if (check_errors())
		{
			if (g_data.file1 && g_data.file2 && g_data.s1[0] && g_data.s2[0])
			{
				g_ret = 0;
				printf("working\n");
			}
		}
	}
	else
		ft_error("Syntax Error: ./pipex file1 cmd1 cmd2 file2\n");
	return (g_ret);
}