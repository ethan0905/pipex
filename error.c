/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:37:14 by esafar            #+#    #+#             */
/*   Updated: 2021/12/30 16:37:23 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i + 1 < ac + 1)
	{
		j = 0;
		while (av[i][j] != '\0')
			j++;
		if (j == 0)
		{
			ft_putstr_fd("pipex: Invalid argument\n", 2);
			basic_exit();
		}
		i++;
	}
}
