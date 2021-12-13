
SRCS	= ft_printf_bonus.c write_args_bonus.c

OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

AR		= ar rc

RM		= rm -f

define libft_make
	cd printf_libft && ${MAKE} $(1) && cd ..
endef

.c.o:
			gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			$(call libft_make, libft.a)
			@echo "\033[95m\nCompiling printf 🐳...\033[0m"
			${AR} ${NAME} ${OBJS}
			ranlib ${NAME}

clean:
			$(call libft_make, clean)
			${MAKE} only_clean

only_clean:
			@echo "\033[91m\nclean printf 🐕 \033[0m"
			${RM} ${OBJS} ${OBJS_B}

fclean:		only_clean
			$(call libft_make, fclean)
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re

