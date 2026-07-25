/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 05:46:15 by joschmun          #+#    #+#             */
/*   Updated: 2026/07/25 12:30:25 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYHOOK_H
# define KEYHOOK_H

# include "init.h"
# include "cleanup.h"

int	handle_keypress(int keycode, t_game *game);
int	handle_keyrelease(int keycode, t_game *game);

#endif
