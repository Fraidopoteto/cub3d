/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:53:12 by jschmunk          #+#    #+#             */
/*   Updated: 2026/07/25 14:11:37 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../../inc/libft/libft.h"

char	*get_next_line(int fd);
char	*ft_readbuff(int fd, char ve);
char	*ft_getline(char ve);
char	*ft_restofline(char *save);
int		ft_firstreadbuff(int fd, char *save);

#endif
