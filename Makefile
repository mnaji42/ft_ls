# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/25 23:48:21 by najimehdi         #+#    #+#              #
#    Updated: 2020/04/27 16:53:49 by najimehdi        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
.SILENT:
endif

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
FT_PRINTF_DIR = ./ft_printf/

SRC_FILES = main.c utils.c list.c sort_list.c display.c display_content.c
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
FT_PRINTF = $(addprefix $(FT_PRINTF_DIR), libftprintf.a)

all: $(OBJ) $(LIBFT) $(FT_PRINTF) $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@gcc $(FLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)
$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(NAME): $(OBJ)
	@gcc $(OBJ) -L $(LIBFT_DIR) -lft $(FT_PRINTF) -o $(NAME)
	@echo "\033[32m$(NAME) generated!\033[0m"

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re obj