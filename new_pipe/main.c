#include "pipex.h"

void error_file(char *file)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
}
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
int 	ft_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	exit(127);
}

void	ft_free(char *tmp)
{
	free(tmp);
	tmp = NULL;
}
// check the leaks if found
int main(int ac, char **av, char **envp)
{
	g_ret = 0;
	if (ac != 5)
	{
		ft_putstr_fd("Syntax Error: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_FAILURE);
	}
	g_data.inp = open(av[1], O_RDONLY);
	if (g_data.inp < 0)
		error_file(av[1]);
	g_data.out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (g_data.out < 0)
	{
		error_file(av[4]);
		exit(EXIT_FAILURE);
	}
	ft_stock_env(envp);
	g_data.s1 = ft_split(av[2], ' ');
	g_data.s2 = ft_split(av[3], ' ');
	if (g_data.s1[0] && search_path(g_data.s1[0], 1) == 0)
		ft_not_found(g_data.s1[0]);
	if (g_data.s2[0] && search_path(g_data.s2[0], 2) == 0)
		ft_not_found(g_data.s2[0]);
	ft_pipe();
	return (g_ret);
}