
SRCS	= ft_isdigit.c ft_strlen.c ft_strlcpy.c ft_atoi.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_power.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

AR		= ar rc

RM		= rm -f

.c.o:
			gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			@echo "\033[95m\nCompiling printf's libft...\033[0m"
			${AR} ${NAME} ${OBJS}
			ranlib ${NAME}

clean:
			@echo "\033[91m\nclean printf's libft\033[0m"
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re

