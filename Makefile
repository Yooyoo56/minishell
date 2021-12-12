
SRC_DIR	= src/
SRCS	= main.c \
		  ft_utils.c \
		  parsing/ft_parse_cmds.c \
		  parsing/ft_parsing_utils.c \
		  parsing/ft_parsing_err.c

OBJ_DIR	= obj/
OBJS	= ${SRCS:.c=.o}
OBJS	:= $(addprefix ${OBJ_DIR}, ${OBJS})

NAME	= minishell

CC		= gcc #-g -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

define libft_make
	cd libft && ${MAKE} $(1) && cd ..
endef

${OBJ_DIR}%.o: ${SRC_DIR}%.c
		mkdir -p ${OBJ_DIR}
		mkdir -p ${OBJ_DIR}/parsing	
		${CC} ${CFLAGS} -c $< -o $@ -I /Users/$(USER)/.brew/opt/readline/include


all:	${NAME}

${NAME}:	${OBJS}
			$(call libft_make, libft.a)
			@echo "\033[95m\nGenerating executable...\033[0m"
			${CC} -o ${NAME} ${OBJS} -Llibft -lft -lreadline -ltermcap -L /Users/$(USER)/.brew/opt/readline/lib

clean:	only_clean
		$(call libft_make, clean)

only_clean:
		${RM} ${OBJS}
		rm -rf ${OBJ_DIR}

fclean:	only_clean
		$(call libft_make, fclean)
	   	${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re

