/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:33:41 by esafar            #+#    #+#             */
/*   Updated: 2021/12/30 16:33:42 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	basic_exit(void)
{
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	exit(0);
}

void	close_data_fds(t_data *data)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->fdin);
	close(data->fdout);
}

void	display_error(char *file_name, t_data *data, int event)
{
	if (event == 1)
	{
		ft_putstr_fd("pipex: ", STDERR);
		write(STDERR, file_name, str_search(file_name, '\0'));
		ft_putstr_fd(": No such file or directory\n", STDERR);
	}
	else if (event == 2)
	{
		ft_putstr_fd("pipex: ", STDERR);
		write(STDERR, file_name, str_search(file_name, '\0'));
		ft_putstr_fd(": Wrong rights on file\n", STDERR);
	}
	else if (event == 3)
	{
		ft_putstr_fd("pipex: ", STDERR);
		write(STDERR, file_name, str_search(file_name, '\0'));
		ft_putstr_fd(": Wrong rights on file\n", STDERR);
		close(data->fdin);
	}
	basic_exit();
}

void	free_ft_split_array(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
