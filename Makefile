NAME		:= pipex

SRC_DIR		:= src
OBJ_DIR		:= obj
LIB_DIR		:= lib

LIBFT_DIR	:= libft

LIBFT		:= $(LIB_DIR)/libft.a

SRC_FILES	:= main.c utils.c ft_printf.c ft_printf_utils.c get_next_line.c \
               get_next_line_utils.c pipeline.c
SRC			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# TODO
CC			:= clang
CPPFLAGS	:= -I include -I $(LIBFT_DIR) -MMD -MP
CFLAGS		:= -Wall -g#-fsanitize=address#-Werror -Wextra
LDFLAGS		:= -L$(LIB_DIR)#-fsanitize=address
LDLIBS		:= -lft

.PHONY:	all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)

$(LIBFT): $(LIB_DIR)
	$(MAKE) --directory=$(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(LIB_DIR):
	mkdir -p $@

clean:
	rm -rv $(OBJ_DIR)
	$(MAKE) clean --directory=$(LIBFT_DIR)

fclean: clean
	rm $(NAME)
	$(MAKE) fclean --directory=$(LIBFT_DIR)

re: fclean all

-include $(OBJ:.o=.d)
