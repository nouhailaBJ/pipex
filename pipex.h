/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:19:23 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/19 13:04:50 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
typedef struct s_pipex
{
	char	**s1;
	char	**s2;
	int		inp;
	int		out;
	int		fd[2];
	pid_t	pid;
	char	**envp;
	int		status;
}			t_pipex;
t_pipex	g_data;
int		g_ret;
void	ft_pipe(void);
char	**ft_split(char const *s, char c);
char	*join_path(char const *s1, char const *s2);
int		search_path(char *line, int nb);
void	ft_not_found(char *cmd);
void	stock_args(char **av, char **envp);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_stock_env(char **envp);
#endif
