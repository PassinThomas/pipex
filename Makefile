# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 17:12:27 by tpassin           #+#    #+#              #
#    Updated: 2024/05/08 19:11:03 by tpassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = libft.a

SRCS = srcs/utils.c \
	   srcs/main.c \

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -g3 -g -Wall -Wextra -Werror

LFLAGS = -L./libft -lft

RM = rm -f

all: ${NAME}

$(NAME): ${OBJS}
	$(MAKE) -C ./libft
	${CC} ${OBJS} ${LFLAGS} -o $(NAME)
    
%.o:%.c
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS}
	$(MAKE) -C ./libft clean

fclean: clean
	${RM} ${NAME}
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY:  all clean fclean re