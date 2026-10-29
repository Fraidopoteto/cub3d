/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:35:48 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 13:36:15 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_texture_path(char *line, int i)
{
	int		start;
	int		len;
	char	*path;

	while (line[i] == '\t' || line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	if (len <= 0)
		return (NULL);
	path = ft_substr(line, start, len);
	return (path);
}
