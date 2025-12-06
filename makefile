# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I include
RM		= rm -f
MKDIR	= mkdir -p

SRC_DIR	= src

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/init_philo.c \
		  $(SRC_DIR)/philo_utils.c \
		  $(SRC_DIR)/philo_routine.c \
		  $(SRC_DIR)/monitor.c \
		  $(SRC_DIR)/threading.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
