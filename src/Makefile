CC = gcc++
FLAGS = -Wall -Wextra -Werror -std=c++17
CFLAGS = -Wall -Werror -Wextra

LIB_NAME = s21_matrix_oop

SRCS=$(wildcard s21_*.cpp)

OBJS=$(SRCS:.c=.o)

all: $(LIB_NAME).a test clean

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

test:
	@rm -rf build
	@mkdir build
	@cd build && cmake ../ && make && ./main

clean:

	rm -rf *.o test *.a