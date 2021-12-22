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

int	open_file(char *file_name, int mode)
{
	if (mode == INFILE)
	{
		if (access(file_name, F_OK))
		{
			ft_putstr_fd("pipex: ", STDERR);
			write(STDERR, file_name, str_search(file_name, '\0'));
			ft_putstr_fd(": No such file or directory\n", STDERR);
			return (STDIN);
		}
		return (open(file_name, O_RDONLY));
	}
	else if (mode == OUTFILE)
		return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	return (-1);
}

void	exec_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (str_search(args[0], '/') > -1)
		path = args[0];
	else
		path = get_path(args[0], env);
	execve(path, args, env);
	ft_putstr_fd("pipex: ", STDERR);
	write(STDERR, cmd, str_search(cmd, '\0'));
	ft_putstr_fd(": command not found\n", STDERR);
	exit(127);
}

void	proceed_processes(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (fdin == STDIN)
			exit(1);
		else
			exec_cmd(cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fdin;
	int	fdout;

	i = 2;
	if (ac >= 5)
	{
		fdin = open_file(av[1], INFILE);
		fdout = open_file(av[ac - 1], OUTFILE);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		while (i < ac - 2)
		{
			if (i == 2)
				proceed_processes(av[i++], env, fdin);
			else
				proceed_processes(av[i++], env, STDOUT);
		}
		exec_cmd(av[i], env);
	}
	else
		ft_putstr_fd("Wrong number of arguments.\n", STDERR);
	return (0);
}
