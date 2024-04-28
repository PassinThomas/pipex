# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 07:12:52 by tpassin           #+#    #+#              #
#    Updated: 2024/03/23 08:15:47 by tpassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	ft_atoi \
ft_bzero \
ft_calloc \
ft_isalnum \
ft_isalpha \
ft_isascii \
ft_isdigit \
ft_isprint \
ft_memchr \
ft_memcmp \
ft_memcpy \
ft_memmove \
ft_memset \
ft_putchar_fd \
ft_putendl_fd \
ft_putnbr_fd \
ft_putstr_fd \
ft_strchr \
ft_strdup \
ft_strlcat \
ft_strlcpy \
ft_strlen \
ft_strncmp \
ft_strrchr \
ft_tolower \
ft_toupper \
ft_strjoin	\
ft_substr \
ft_strnstr \
ft_striteri \
ft_strmapi \
ft_strtrim \
ft_split \
ft_itoa \
ft_free \
ft_strcmp \
get_next_line \
ft_strjoin_bonus \

SRCS 	= $(addsuffix .c, ${SRC})

OBJS	= ${SRCS:.c=.o}

BONUS	=	ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstiter.c \
ft_lstclear.c \
ft_lstmap.c \
ft_lstdelone.c \
ft_lstadd_back.c \

BONUS_OBJS	= ${BONUS:.c=.o}

CC	= cc
RM	= rm -f
AR	= ar rc

CFLAGS	= -g3 -g -Wall -Werror -Wextra

NAME = libft.a

all:		${NAME} bonus

${NAME}:	${OBJS}
				${AR} ${NAME} ${OBJS}		

%o :%c
		${CC} ${CFLAGS} -c $< -o $@

clean:
		${RM} ${OBJS} ${BONUS_OBJS}

fclean:	clean
				${RM} ${NAME} ${BONUS_OBJS}

re :	fclean all

bonus:		$(BONUS_OBJS)
				${AR} $(NAME) $(BONUS_OBJS)

.PHONY: all bonus clean fclean re
