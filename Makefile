# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 20:09:41 by oelbouha          #+#    #+#              #
#    Updated: 2023/02/13 20:09:54 by oelbouha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc

CFLAGS := -Wall -Wextra -Werror

RM := rm -f

SRC := philo.c \
		utils.c

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


clean: 
	@${RM} $(OBJ)

fclean: clean
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re