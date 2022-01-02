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

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.i = 2;
	check_args(av, ac);
	if (ac == 5)
	{
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
	else
		ft_putstr_fd("Wrong number of arguments.\n", STDERR);
	close_data_fds(&data);
	return (0);
}
