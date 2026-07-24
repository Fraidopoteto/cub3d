/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 04:51:38 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/24 13:36:05 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "init.h"

int		close_game(t_game *game);
void	cleanup(t_game *game);

#endif