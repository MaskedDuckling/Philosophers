# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 15:22:06 by eydupray          #+#    #+#              #
#    Updated: 2022/01/21 17:00:43 by eydupray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
INC = philo.h
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

SRCS	=	main.c utils.c libft.c init.c thread_utils.c

OBJS = $(SRCS:.c=.o)

.c.o:
		clang ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -lpthread -o $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

po:		all clean

re:		fclean all

.PHONY:	all clean fclean re