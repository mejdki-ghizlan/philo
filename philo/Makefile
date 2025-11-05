NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror	-pthread

SRCS = utils.c \
       init.c \
	   routine.c \
	   parsing.c \
	   philo.c \
		monitor.c \



OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

%.o: %.c philosopher.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
