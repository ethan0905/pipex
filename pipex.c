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

int	strsearch(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strndup(char *src, int n)
{
	char *dest;
	int i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*create_path(char *path, char *cmd)
{
	int i;
	int j;
	char *dest;

	dest = (char *)malloc(sizeof(char) * (strsearch(path, 0) + strsearch(cmd, 0) + 2));
	if (!dest)
		return NULL;
	i = -1;
	while (path[++i])
		dest[i] = path[i];
	//securiser car '/' seulement si la commande est donne normalement
	dest[i] = '/';
	i++;
	j = -1;
	while (cmd[++j])
		dest[i + j] = cmd[j];
	dest[i + j] = '\0';
	return (dest);
}

int	find_in_env(char **src, char *to_find)
{
	int	i;

	i = 0;
	while (src[i] && ft_strncmp(src[i], to_find, ft_strlen(to_find)))
		i++;
	return (i);
}

char	*get_path(char *cmd, char **env)
{
	char *path;
	char *dir;
	char *bin;
	int i;

	i = 0;
	i = find_in_env(env, "PATH=");
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && strsearch(path, ':') > -1)
	{
		dir = ft_strndup(path, strsearch(path, ':'));
		bin = create_path(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
		{
			// printf("returned BIN\n");
			return (bin);
		}
		free(bin);
		path += strsearch(path, ':') + 1;
	}
	// printf("returned CMD\n");
	return (cmd);
}

// void	open_file(char *filename, char **env, char **av)
// {
// 	int i = 0;
// 	char *pwd;
// 	char *path_to;
// 	char *new_path;

// 	char **cmd;

// 	i = find_in_env(env, "PWD=");
// 	pwd = env[i] + 4;
// 	path_to = ft_strjoin(pwd, "/");
// 	new_path = ft_strjoin(path_to, filename);
// 	ft_strdel(&path_to);
// 	check_path(new_path);

// 	printf("open file path : %s\n", new_path);
// 	ft_strdel(&new_path);
// }

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int	open_file(char *file_name, int mode)
{
	if (mode == 0)
	{
		if (access(file_name, F_OK))
		{
			ft_putstr_fd("pipex: \n", 2);
			write(2, file_name, strsearch(file_name, '\0'));
			ft_putstr_fd(": No such file or directory\n", 2);
			return (STDIN);
		}
		return (open(file_name, O_RDONLY));
	}
	else
		return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

void	exec (char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (strsearch(args[0], '/') > -1)
		path = args[0];
	else
		path = get_path(args[0], env);
	execve(path, args, env);
	write(2, "pipex: ", 7);
	write(2, cmd, strsearch(cmd, 0));
	write(2, ": command not found\n", 20);
	// exit(127);
}

int main(int ac, char **av, char **env)
{
	// open_file(av[1], env, av);

	exec(get_path(av[1], env), env);
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
