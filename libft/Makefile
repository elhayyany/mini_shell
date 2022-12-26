# -*- Makefile -*-

CC = gcc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g
SOURCE = ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcat.c ft_strnstr.c ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlcpy.c \
ft_strrchr.c ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strlen.c ft_substr.c ft_isalnum.c ft_isprint.c ft_memmove.c ft_strncmp.c \
ft_tolower.c ft_toupper.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_split.c
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
all : $(NAME)

SRC_OBJECT = $(SOURCE:.c=.o)
BONUS_OBJECT = $(BONUS:.c=.o)

$(NAME): $(SRC_OBJECT)
	ar -rc $(NAME) $(SRC_OBJECT)

bonus : $(BONUS_OBJECT)
	ar -rc $(NAME) $(BONUS_OBJECT)
clean: 
	rm -f $(SRC_OBJECT) $(BONUS_OBJECT)
fclean:clean
	rm -f libft.a 
re:fclean all bonus
