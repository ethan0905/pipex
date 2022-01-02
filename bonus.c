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

void	here_doc(char *av, t_data *data)
{
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

void	start_piping(int ac, char **av, char **env, t_data *data)
{
	dup2(data->fdin, STDIN);
	dup2(data->fdout, STDOUT);
	if (data->heredoc)
		data->i = 3;
	else
		data->i = 2;
	while (data->i < ac - 2)
	{
		if (data->i == 2)
			proceed_processes(av[data->i++], env, data->fdin, data);
		else
			proceed_processes(av[data->i++], env, STDOUT, data);
	}
	exec_cmd(av[data->i], env, data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.heredoc = 0;
	check_args(av, ac);
	if (ac >= 5 && strncmp(av[1], "here_doc", 8) == 0)
	{
		here_doc(av[2], &data);
		data.fdout = open_file(av[ac - 1], OUTFILE, &data);
		data.heredoc = 1;
		start_piping(ac, av, env, &data);
	}
	else if (ac >= 5 && strncmp(av[1], "here_doc", 8) != 0)
	{
		data.fdin = open_file(av[1], INFILE, &data);
		data.fdout = open_file(av[ac - 1], OUTFILE, &data);
		start_piping(ac, av, env, &data);
	}
	else
		ft_putstr_fd("Wrong number of arguments.\n", STDERR);
	close_data_fds(&data);
	return (0);
}
