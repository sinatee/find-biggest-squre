NAME = bsq

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
       map_reader.c \
       map_checker.c \
       stdin_reader.c \
       solve_bsq.c

OBJS = $(SRCS:.c=.o)

HEADER = bsq.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re