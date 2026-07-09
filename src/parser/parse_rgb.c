/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:35:50 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/09 14:02:45 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void _free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	*get_rgb(char *line, int i)
{
	char	**split;
	int		*rgb;
	int		count;

	count = 0;
	while (line[i] && (line[i] < '0' && line[i] > '9'))
		i++;
	split = ft_split(&line[i], ',');
	if (!split)
		return (NULL);
	while (split[count])
		count++;
	if (count != 3)
		return (error_NULL("Error\nwrong number of RGB elements\n"));
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		_free_split(split);
		return (NULL);
	}
	count = 0;
	while (count++ != 2)
		rgb[count] = ft_atoi(split[count]);
	return (rgb);
}
