/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:43 by esafar            #+#    #+#             */
/*   Updated: 2021/12/15 11:28:45 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_path(char *path)
{
	if (access(path, F_OK) == -1)
		ft_putstr_fd("open: No such file or directory.\n", 2);
	else if (access(path, R_OK) == -1)
		ft_putstr_fd("open: permission denied.\n", 2);
	else if (access(path, W_OK) == -1)
		ft_putstr_fd("open: permission denied.\n", 2);
	else
		return (1);
	return (0);
}

void	ft_strdel(char **str)
{
	while (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

int	find_pwd_pos(char **src, char *to_find)
{
	int	i;

	i = 0;
	while (src[i] && ft_strncmp(src[i], to_find, ft_strlen(to_find)))
		i++;
	return (i);
}

void	open_file(char *filename, char **envp)
{
	int i = 0;
	char *pwd;
	char *path_to;
	char *new_path;

	i = find_pwd_pos(envp, "PWD=");
	pwd = envp[i] + 4;
	path_to = ft_strjoin(pwd, "/");
	new_path = ft_strjoin(path_to, filename);
	ft_strdel(&path_to);
	if (check_path(new_path))
		printf("Valid path !\n");

	ft_strdel(&new_path);
}

int main(int ac, char **av, char **envp)
{
	open_file(av[1], envp);

	return 0;
}

// int	main(int ac, char **av, char **envp) {
// 	int fd[2];
// 	char *ls[] = {"ls", "-la", NULL};
// 	char *cat[] = {"cat", "infile", NULL};

// 	if (pipe(fd) == -1) {
// 		return (-1);
// 	}

// 	int pid1 = fork();
// 	if (pid1 < 0) {
// 		return -1;
// 	}

// 	if (pid1 == 0) {
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve("/usr/bin/cat", cat, NULL);
// 	}

// 	int pid2 = fork();
// 	if (pid2 < 0) {
// 		return -1;
// 	}

// 	if (pid2 == 0) {
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("wc", "wc", "-l", NULL);
// 	}

// 	close(fd[0]);
// 	close(fd[1]);

// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }
