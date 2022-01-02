/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 09:05:29 by esafar            #+#    #+#             */
/*   Updated: 2021/06/16 16:29:05 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../pipex.h"

int		get_next_line(int fd, char **line);

// size_t	ft_strlen(char *str);
char	*ft_strdup(char *src);
int		ft_isnewline(char *s);
// char	*ft_strjoin(char *save, char *buff);

#endif
