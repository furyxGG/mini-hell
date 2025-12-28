NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Werror -Wextra

SRC_DIR     = srcs
INC_DIR     = inc
LIB_DIR     = libs

LIBFT_DIR   = $(LIB_DIR)/libft
LIBFT_A     = $(LIBFT_DIR)/libft.a

SRCS        = main.c $(wildcard $(SRC_DIR)/*.c)
OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS        = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
