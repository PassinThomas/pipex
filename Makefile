# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 15:13:47 by tpassin           #+#    #+#              #
#    Updated: 2024/05/23 21:13:57 by tpassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

LIBFT = libft.a

SRCS = srcs/mandatory/utils.c \
	   srcs/mandatory/main.c \

BONUS = srcs/bonus/bonus_utils.c \
	   	srcs/bonus/bonus_main.c \

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}


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
	${RM} ${OBJS} ${BONUS_OBJS}
	$(MAKE) -C ./libft clean

fclean: clean
	${RM} ${NAME} ${NAME_BONUS}
	$(MAKE) -C ./libft fclean

re: fclean all

bonus: ${BONUS_OBJS}
	$(MAKE) -C ./libft
	${CC} ${BONUS_OBJS} ${LFLAGS} -o $(NAME_BONUS)

.PHONY:  all clean fclean re bonus  