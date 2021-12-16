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

void	free_array(char ***str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while ((*str)[i])
	{
		ft_strdel(*str + i);
		i++;
	}
	free(*str);
	*str = NULL;
}

char		*search_path(char **paths, char *cmd)
{
	int				i;
	char			*path;
	char			*part_path;

	i = 0;
	while (paths[i] && cmd[1] != '/')
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		ft_strdel(&part_path);
		if (access(path, F_OK) == 0)
			return (path);
		ft_strdel(&path);
		i++;
	}
	if (cmd[0] == '/')
		return ("");
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*get_path(char **envp, char **cmd)
{
	char **paths;
	char *path;

	paths = ft_split(envp[0] + 5, ':');
	path = search_path(paths, *cmd);
	free_array(&paths);
	return (path);
}

int	find_pwd_pos(char **src, char *to_find)
{
	int	i;

	i = 0;
	while (src[i] && ft_strncmp(src[i], to_find, ft_strlen(to_find)))
		i++;
	return (i);
}

void	open_file(char *filename, char **envp, char **av)
{
	int i = 0;
	char *pwd;
	char *path_to;
	char *new_path;

	char **cmd;

	i = find_pwd_pos(envp, "PWD=");
	pwd = envp[i] + 4;
	path_to = ft_strjoin(pwd, "/");
	new_path = ft_strjoin(path_to, filename);
	ft_strdel(&path_to);
	if (check_path(new_path))
	{
		cmd = ft_split(av[2], ' ');
		execve(get_path(envp, cmd), cmd, envp);
		printf("Valid path !\n");
	}

	ft_strdel(&new_path);
}

int main(int ac, char **av, char **envp)
{
	open_file(av[1], envp, av);

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
