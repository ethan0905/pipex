/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:35:42 by esafar            #+#    #+#             */
/*   Updated: 2022/01/02 17:35:50 by esafar           ###   ########.fr       */
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
