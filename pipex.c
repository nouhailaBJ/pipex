#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"

/*
the parent process treats the first command, 
write its output in the first pipe and create a child which will treat the second command
and write its outputin the second pipe, meanwhile this child will create a sub-child 
which will treat the third command.
*/
void	ft_pipe(char **s1, char **s2, int in, int out)
{
	int fd[2];
	pid_t pid;
	if (pipe(fd) != 0)
		exit(EXIT_FAILURE);
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);

	if (pid == 0)
	{
		dup2(fd[1], 1);
		dup2(in, 0);
		close(fd[0]);
		close(fd[1]);
		execvp(s1[0], s1);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd[0], 0);
		dup2(out, 1);
		close(fd[0]);
		close(fd[1]);
		execvp(s2[0], s2);
		exit(EXIT_FAILURE);
	}
}
/************* join_path ***********/
char		*join_path(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) == 0)
		return (NULL);
	while (s1[j] != '\0')
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '/';
	j++;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
/************* END join_path ***********/
int search_command(char *str)
{
    char *path;
    char **all_path;
    struct stat stats;
	int i;

    if (!str)
        return (0);
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = 0;
	while (all_path[i])
	{
		path = join_path(all_path[i], str);
		if (stat(path, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
				return (1);
			else{
				ft_putstr_fd("permisison denied\n", 1);
            }
		}
		i++;
	}
	return (0);
}
int main(int ac, char **av, char **envp)
{
    char  **s1;
    char **s2;
    int fd[2];
    if (ac == 5)
    {
        s1 = ft_split(av[2], ' ');
        s2 = ft_split(av[3], ' ');
        if (search_command(s1[0]) == 0 || search_command(s2[0]) == 0)
        {
            ft_putstr_fd("Error : command not found \n", 1);
            return (0);
        }
    	fd[0] = open(av[1], O_RDONLY); // input
		fd[1] = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        if (fd[0] < 0)
        {
            perror("pipex");
            exit(EXIT_FAILURE);
        }
        if (fd[1] < 0)
        {
            perror("pipex");
            exit(EXIT_FAILURE);
        } 
        ft_pipe(s1, s2, fd[0], fd[1]);
    }else
        ft_putstr_fd("Syntax : Error \n", 1);
    return (0);
}