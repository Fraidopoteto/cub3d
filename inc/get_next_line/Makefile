# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 18:39:31 by jschmunk          #+#    #+#              #
#    Updated: 2026/07/24 16:17:01 by joschmun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

SRC = get_next_line.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=1

COMPILE = $(CC) $(CFLAGS) -c

LIB = ar -rcs $(NAME)

%.o : %.c
	$(COMPILE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(LIB) $(OBJ)
	

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re