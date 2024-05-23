# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 07:12:52 by tpassin           #+#    #+#              #
#    Updated: 2024/05/23 20:18:02 by tpassin          ###   ########.fr        #
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
ft_printf \
ft_print_hex \
ft_putchar \
ft_putnbr \
ft_putstr \
ft_unsigned_nb \
ft_put_p \
ft_lstnew \
ft_lstadd_front \
ft_lstsize \
ft_lstlast \
ft_lstiter \
ft_lstclear \
ft_lstmap \
ft_lstdelone \
ft_lstadd_back \

SRCS 	= $(addsuffix .c, ${SRC})

OBJS	= ${SRCS:.c=.o}

CC	= cc
RM	= rm -f
AR	= ar rc

CFLAGS	= -g3 -g -Wall -Werror -Wextra

NAME = libft.a

all:		${NAME}

${NAME}:	${OBJS}
				${AR} ${NAME} ${OBJS}		

%o :%c
		${CC} ${CFLAGS} -c $< -o $@

clean:
		${RM} ${OBJS}

fclean:	clean
				${RM} ${NAME}

re :	fclean all

.PHONY: all clean fclean re
