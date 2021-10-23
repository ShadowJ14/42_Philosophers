NAME = ./philo
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
INCLUDE_DIRS := includes
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
SRC = $(call rwildcard,src,*.c)
OBJ := $(SRC:.c=.o)
RM = rm -f
MAKE = make
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = gcc

all: $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDES)


clean:
	$(RM)   $(OBJ)

fclean: clean
		$(RM)   $(NAME)

re: fclean  all

bonus: $(NAME)

.PHONY:         all clean fclean bonus
