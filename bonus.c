/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:36:15 by esafar            #+#    #+#             */
/*   Updated: 2021/12/29 18:18:27 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file_name, int mode, t_data *data)
{
	if (mode == INFILE)
	{
		if (access(file_name, F_OK))
			display_error(file_name, data, 1);
		else if (access(file_name, R_OK))
			display_error(file_name, data, 2);
		return (open(file_name, O_RDONLY | O_TRUNC, 0644));
	}
	else if (mode == OUTFILE)
	{
		if (access(file_name, W_OK))
			display_error(file_name, data, 3);
		return (open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	}
	return (-1);
}

void	exec_cmd(char *cmd, char **env, t_data *data)
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
	close(data->fdin);
	close(data->fdout);
	free_ft_split_array(args);
	basic_exit();
}

void	proceed_processes(char *cmd, char **env, int fdin, t_data *data)
{
	pid_t	pid;

	pipe(data->pipefd);
	pid = fork();
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
			exec_cmd(cmd, env, data);
	}
}

void	here_doc(char *av, t_data *data)
{
	// int		file;
	char	*buf;

	data->file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->file < 0)
		exit(0);
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &buf) < 0)
			exit(0);
		if (!ft_strncmp(av, buf, ft_strlen(av) + 1))
			break ;
		write(data->file, buf, ft_strlen(buf));
		write(data->file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(data->file);
	data->fdin = open(".heredoc_tmp", O_RDONLY);
	if (data->fdin < 0)
	{
		unlink(".heredoc_tmp");
		exit(0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.i = 2;
	check_args(av, ac);
	if (ac >= 5 && strncmp(av[1], "here_doc", 8) == 0)
	{
		if (strncmp(av[1], "here_doc", 8) == 0)
		{
			here_doc(av[2], &data);
			data.i++;
		}
		else
			data.fdin = open_file(av[1], INFILE, &data);
		data.fdout = open_file(av[ac - 1], OUTFILE, &data);
		dup2(data.fdin, STDIN);
		dup2(data.fdout, STDOUT);
		while (data.i < ac - 2)
		{
			if (data.i == 2)
				proceed_processes(av[data.i++], env, data.fdin, &data);
			else
				proceed_processes(av[data.i++], env, STDOUT, &data);
		}
		exec_cmd(av[data.i], env, &data);
	}
	else if (ac >= 5 && strncmp(av[1], "here_doc", 8) != 0)
	{
		
	}
	else
		ft_putstr_fd("Wrong number of arguments.\n", STDERR);
	close_data_fds(&data);
	return (0);
}
