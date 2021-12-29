/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:28:43 by esafar            #+#    #+#             */
/*   Updated: 2021/12/27 19:30:04 by esafar           ###   ########.fr       */
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
		else if (access(file_name, R_OK))
		{
			ft_putstr_fd("pipex: ", STDERR);
			write(STDERR, file_name, str_search(file_name, '\0'));
			ft_putstr_fd(": Wrong rights on file\n", STDERR);
			return (STDIN);
		}
		return (open(file_name, O_RDONLY | O_TRUNC, 0644));
	}
	else if (mode == OUTFILE)
	{
		// if (access(file_name, W_OK))
		// {
		// 	ft_putstr_fd("pipex: ", STDERR);
		// 	write(STDERR, file_name, str_search(file_name, '\0'));
		// 	ft_putstr_fd(": Wrong rights on file\n", STDERR);
		// 	exit(0);
		// }
		return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	}
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

void	proceed_processes(char *cmd, char **env, int fdin, t_data *data)
{
	pid_t	pid;

	pipe(data->pipefd);
	pid = fork();
	printf("pid = %d", pid);
	if (pid)
	{
		close(data->pipefd[1]);
		dup2(data->pipefd[0], STDIN);
		close(data->pipefd[0]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(data->pipefd[0]);
		dup2(data->pipefd[1], STDOUT);
		close(data->pipefd[1]);
		if (fdin == STDIN)
			exit(1);
		else
			exec_cmd(cmd, env);
	}
}

void	check_error(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i == 0)
	{
		ft_putstr_fd("pipex: Command not found\n", 2);
		close(data->fdin);
		close(data->fdout);
		close(STDIN);
		close(STDOUT);
		close(STDERR);
		exit(0);
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	int	i;
	t_data data;

	i = 2;
	if (ac == 5)
	{
		data.fdin = open_file(av[1], INFILE);
		data.fdout = open_file(av[ac - 1], OUTFILE);
		dup2(data.fdin, STDIN);
		dup2(data.fdout, STDOUT);
		while (i < ac - 2)
		{
			check_error(av[i], &data);
			if (i == 2)
				proceed_processes(av[i++], env, data.fdin, &data);
			else
				proceed_processes(av[i++], env, STDOUT, &data);
		}
		exec_cmd(av[i], env);
	}
	else
		ft_putstr_fd("Wrong number of arguments.\n", STDERR);
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	close(data.fdin);
	close(data.fdout);
	return (0);
}
