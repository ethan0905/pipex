/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:11:49 by esafar            #+#    #+#             */
/*   Updated: 2021/12/16 15:11:53 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

# define BUFFER_SIZE 1

typedef struct s_data
{
	int	pipefd[2];
	int	fdin;
	int	fdout;
	int i;
	int file;
}				t_data;

//get_path
char	*get_path(char *cmd, char **env);
char	*create_path(char *path, char *cmd);
int		str_search(char *str, char c);
int		find_in_env(char **src, char *to_find);
char	*ft_strndup(char *src, int n);

//exit
void	free_ft_split_array(char **args);
void	display_error(char *file_name, t_data *data, int event);
void	close_data_fds(t_data *data);
void	basic_exit(void);

//error
void	check_args(char **av, int ac);

#endif
