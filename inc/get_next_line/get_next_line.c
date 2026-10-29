/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:53 by jschmunk          #+#    #+#             */
/*   Updated: 2026/07/08 12:22:38 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_join(int fd, char	*saved)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	if (!saved)
		saved = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(saved, buffer);
		free(saved);
		saved = temp;
		if (ft_strchr(saved, '\n'))
			break ;
	}
	free(buffer);
	return (saved);
}

char	*savedtilnl(char *saved, char c)
{
	int		i;
	int		j;
	char	*tilnl;

	i = 0;
	j = 0;
	while (saved[i] && saved[i] != c)
		i++;
	tilnl = (char *)malloc((sizeof(char) * (i + 2)));
	if (!tilnl)
		return (NULL);
	while (j <= i)
	{
		tilnl[j] = saved[j];
		j++;
	}
	tilnl[i + 1] = '\0';
	return (tilnl);
}

char	*savedaftnl(char *saved, char c)
{
	int		i;
	int		j;
	char	*aftnl;

	i = 0;
	j = 0;
	while (saved[i] && saved[i] != c)
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	aftnl = (char *)malloc(sizeof(char) * (ft_strlen(saved) - i));
	if (!aftnl)
		return (NULL);
	i++;
	while (saved[i])
		aftnl[j++] = saved[i++];
	aftnl[j] = '\0';
	free(saved);
	return (aftnl);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	saved = read_join(fd, saved);
	if (!saved)
		return (NULL);
	if (ft_strchr(saved, '\n'))
	{
		line = savedtilnl(saved, '\n');
		saved = savedaftnl(saved, '\n');
	}
	else if (ft_strlen(saved) > 0)
	{
		line = savedtilnl(saved, '\0');
		free (saved);
		saved = NULL;
	}
	else if (saved[0] == '\0')
		return (free(saved), saved = NULL, NULL);
	return (line);
}
