# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 17:25:48 by ael-hayy          #+#    #+#              #
#    Updated: 2022/08/09 17:36:20 by ael-hayy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = minishell
FILES = *c  ./executor/*c ./executor/Build_in/*c
OBJECTS = $(FILES:.c=.o)

%.o : %.c
	@cc -c -Wall -Wextra -Werror $<

all:  $(NAME)

$(NAME): $(OBJECTS)
	@cd libft && make && make bonus
	@cd ..
	@$(CC) $(CFLAGS) $(OBJECTS) -g -lreadline -L /Users/akaouan/.brew/opt/readline/lib -I /Users/akaouan/.brew/opt/readline/include  -o $(NAME) libft/libft.a

clean:
	$(RM) *.o
	cd libft && make clean
	cd ../

fclean: clean
	@cd libft && make fclean
	@cd ../
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
