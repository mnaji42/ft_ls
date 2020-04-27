NAME =  libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./Includes/
LIBFT_DIR = ./libft/

SRC_FILES = ft_printf.c printnbr.c printnbrll.c printbase.c printbasell.c print_csp.c printdouble_fd.c print_convert.c print_base_help.c stock_integer_float.c printdouble_help.c printnbr_help.c printnbrll_help.c
LIB_FILES = ft_putstr.c ft_putchar.c ft_putstr_fd.c ft_putchar_fd.c ft_strlen.c ft_printstr.c ft_strchr.c ft_bzero.c ft_putnbr_fd.c ft_atoi.c ft_printnc_fd.c ft_powerof_10.c ft_strdup.c ft_strdel.c
OBJ_FILES = $(SRC_FILES:.c=.o) $(LIB_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
LIB = $(addprefix $(LIBFT_DIR), $(LIB_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: obj $(NAME)

obj:
	@mkdir $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -o $@ -c $<
$(OBJ_DIR)%.o:$(LIBFT_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[32mLibftprintf.a generated !\033[0m"

clean:
	@rm -Rf $(OBJ_DIR)
	@echo "\033[31mObjects deleted !\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mLibftprintf.a deleted !\033[0m"

re: fclean all

bonus : all

.PHONY: all clean fclean re
