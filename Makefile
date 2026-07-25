# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/08 03:44:14 by joschmun          #+#    #+#              #
#    Updated: 2026/07/25 13:08:11 by joschmun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

CC := cc

# ==================== ORDNER ====================
SRC_DIR   := src
OBJ_DIR   := obj
INC_DIR   := inc
LIBFT_DIR := $(INC_DIR)/libft
GNL_DIR   := $(INC_DIR)/get_next_line
MLX_DIR   := $(INC_DIR)/minilibx-linux

# ==================== FLAGS ====================
CFLAGS    := -Wall -Wextra -Werror -O2
CPPFLAGS  := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR) \
             -I$(SRC_DIR) -I$(SRC_DIR)/run -I$(SRC_DIR)/init \
             -I$(SRC_DIR)/window -I$(SRC_DIR)/keyhook -I$(SRC_DIR)/cleanup -I$(SRC_DIR)/parser \
			 -I$(SRC_DIR)/error -I$(SRC_DIR)/image -I$(SRC_DIR)/player -I$(SRC_DIR)/raycast

LDFLAGS   :=
LDLIBS    := -L$(GNL_DIR) -l:get_next_line.a -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Debug / Sanitizer
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -O0
endif
ifeq ($(ASAN), 1)
    CFLAGS += -fsanitize=address
    LDFLAGS += -fsanitize=address
endif

# ==================== SOURCES ====================
SRC :=
vpath %.c $(SRC_DIR)/cleanup
SRC += cleanup.c

vpath %.c $(SRC_DIR)/error
SRC += error.c

vpath %.c $(SRC_DIR)/image
SRC += mini_map.c
SRC += image.c

vpath %.c $(SRC_DIR)/init
SRC += init.c

vpath %.c $(SRC_DIR)/keyhook
SRC += keyhook.c

vpath %.c $(SRC_DIR)/player
SRC += player.c
SRC += move_player.c

vpath %.c $(SRC_DIR)/parser
SRC += parse_map.c
SRC += parse_metadata.c
SRC += parse_rgb.c
SRC += parse_texture.c
SRC += parser.c
SRC += validate_map.c
SRC += validate_metadata.c
SRC += validate_map_utils.c

vpath %.c $(SRC_DIR)/raycast
SRC += raycast.c
SRC += raycast_utils.c

vpath %.c $(SRC_DIR)/run
SRC += main.c
SRC += run.c

vpath %.c $(SRC_DIR)/window
SRC += window.c

OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

# ==================== REGELN ====================
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(GNL_DIR)/get_next_line.a
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@
	@echo "\033[0;32m✓ $(NAME) erfolgreich erstellt!\033[0m"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

# Libft kompilieren
$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR) --no-print-directory

# GNL kompilieren
$(GNL_DIR)/get_next_line.a:
	@make -C $(GNL_DIR) --no-print-directory

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@make -C $(GNL_DIR) clean --no-print-directory

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(GNL_DIR) fclean --no-print-directory

re:
	@make fclean
	@make all

# ==================== DEBUG ====================
valtest:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

.PHONY: all clean fclean re valtest