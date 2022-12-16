CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
LIB_NAME = s21_matrix

SRCS=$(wildcard s21_*.c)

OBJS=$(SRCS:.c=.o)

all: clean $(LIB_NAME).a

clean:
	rm -rf *.o *.a
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o
