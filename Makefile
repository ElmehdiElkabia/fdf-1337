NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
lib = $(LIBFT_DIR)/libft.a

sources = $(wildcard src/*.c)

object = $(sources:.c=.o)

all: $(NAME) 

$(lib):
	make all -C $(LIBFT_DIR)

#  gcc src/main.c src/parser.c src/render.c src/events.c get_next_line/get_next_line.c libft/libft.a -g -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd 

$(NAME): $(object) $(lib)
	$(CC) $(CFLAGS) $(object)  get_next_line/get_next_line.c libft/libft.a -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd -o $(NAME)

clean:
	rm -rf $(object)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

flush: re clean
	make clean -C $(LIBFT_DIR)
	rm -rf $(object)

f: $(object)
	$(CC) $(CFLAGS) $(object) get_next_line/get_next_line.c libft/libft.a -lmlx -lXext -lX11 -lm -o $(NAME)
	make clean

c: $(object)
	$(CC) $(CFLAGS) $(object) get_next_line/get_next_line.c libft/libft.a -lmlx -lXext -lX11 -lm -o $(NAME)

.SECONDARY: $(object)
.PHONY: clean fclean re all