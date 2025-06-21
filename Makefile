NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -I includes
AR := ar rcs
RM := rm -f

SRC_DIR := srcs
BONUS_DIR := bonus

SRC := srcs/ft_isalpha.c srcs/ft_isdigit.c srcs/ft_isalnum.c \
srcs/ft_isascii.c srcs/ft_isprint.c srcs/ft_strlen.c \
srcs/ft_toupper.c srcs/ft_tolower.c srcs/ft_memset.c \
srcs/ft_bzero.c srcs/ft_memcpy.c srcs/ft_memmove.c \
srcs/ft_strncmp.c srcs/ft_memcmp.c srcs/ft_strchr.c \
srcs/ft_strrchr.c srcs/ft_strlcpy.c srcs/ft_strlcat.c \
srcs/ft_strnstr.c srcs/ft_atoi.c srcs/ft_calloc.c \
srcs/ft_strdup.c srcs/ft_substr.c srcs/ft_memchr.c \
srcs/ft_itoa.c srcs/ft_strjoin.c srcs/ft_strtrim.c \
srcs/ft_split.c srcs/ft_strmapi.c srcs/ft_striteri.c \
srcs/ft_putchar_fd.c srcs/ft_putstr_fd.c \
srcs/ft_putendl_fd.c srcs/ft_putnbr_fd.c \
srcs/ft_realloc.c

BONUS := bonus/ft_lstnew_bonus.c bonus/ft_lstadd_front_bonus.c bonus/ft_lstsize_bonus.c \
bonus/ft_lstlast_bonus.c bonus/ft_lstadd_back_bonus.c bonus/ft_lstdelone_bonus.c \
bonus/ft_lstclear_bonus.c bonus/ft_lstiter_bonus.c bonus/ft_lstmap_bonus.c

OBJ			:= $(SRC:.c=.o)
OBJ_BONUS	:= $(BONUS:.c=.o)
OBJ_ALL		:= $(OBJ)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all