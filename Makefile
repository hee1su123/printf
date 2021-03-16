# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 02:39:00 by heeyang           #+#    #+#              #
#    Updated: 2021/03/16 08:36:33 by heeyang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror

SRCS	= ./ft_printf.c ./print_char.c ./print_str.c ./print_ptr.c ./print_di.c\
		  ./print_u.c ./print_x.c ./utils.c ./utils2.c

OBJS	= $(patsubst %.c,%.o,$(SRCS))

$(NAME):
		$(CC) $(CFLAGS) -c $(SRCS)
		ar rc $(NAME) $(OBJS)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
