/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:35:50 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/24 17:05:39 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_rgb_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
}

static int	*return_rgb_error(char **split)
{
	free_rgb_split(split);
	return (NULL);
}

static int	is_valid_rgb_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	*parse_rgb_values(char *str)
{
	char	**split;
	int		*rgb;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	if (i != 3 || !split[0][0] || !split[1][0] || !split[2][0])
		return (return_rgb_error(split));
	if (!is_valid_rgb_number(split[0]) ||
		!is_valid_rgb_number(split[1]) ||
		!is_valid_rgb_number(split[2]))
		return (return_rgb_error(split));
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (return_rgb_error(split));
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	free_rgb_split(split);
	return (rgb);
}

int	*get_rgb(char *line, int offset)
{
	char	*color_str;
	int		*rgb;
	int		count_comma;
	int		i;

	count_comma = 0;
	i = 0;
	if (!line)
		return (NULL);
	while (line[offset] && (line[offset] == ' ' || line[offset] == '\t'))
		offset++;
	while (line[i])
	{
		if (line[i] == ',')
			count_comma++;
		i++;
	}
	if (count_comma != 2)
		return (NULL);
	color_str = ft_strdup(line + offset);
	if (!color_str)
		return (NULL);
	rgb = parse_rgb_values(color_str);
	free(color_str);
	return (rgb);
}
