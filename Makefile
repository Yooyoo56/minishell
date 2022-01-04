# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytak <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 14:49:45 by ytak              #+#    #+#              #
#    Updated: 2022/01/04 07:30:45 by whazami          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	= src/
SRCS	= main.c \
		  ft_utils.c \
		  parsing/ft_generate_new_line.c \
		  parsing/ft_generate_nl_utils.c \
		  parsing/ft_parse_cmds.c \
		  parsing/ft_parsing_err.c \
		  parsing/ft_parse_chevrons.c \
		  parsing/ft_parse_pipes.c \
		  parsing/ft_parsing_utils.c \
		  cmds/ft_cmds_echo.c \
		  cmds/ft_cmds_utils.c \
		  cmds/ft_env_cmds.c \
		  cmds/ft_env_utils.c \
		  cmds/ft_manage_cmds.c \
		  cmds/ft_redirections.c

OBJ_DIR	= obj/
OBJS	= ${SRCS:.c=.o}
OBJS	:= $(addprefix ${OBJ_DIR}, ${OBJS})

NAME	= minishell

CC		= gcc -g3 -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

define libft_make
	cd libft && ${MAKE} $(1) && cd ..
endef

${OBJ_DIR}%.o: ${SRC_DIR}%.c
		mkdir -p ${OBJ_DIR}
		mkdir -p ${OBJ_DIR}/parsing
		mkdir -p ${OBJ_DIR}/cmds
		${CC} ${CFLAGS} -c $< -o $@ -I /Users/$(USER)/homebrew/opt/readline/include


all:	${NAME}

${NAME}:	${OBJS}
			$(call libft_make, libft.a)
			@echo "\033[95m\nGenerating executable 🐥...\033[0m"
			${CC} -o ${NAME} ${OBJS} -Llibft -lft -lreadline -ltermcap -L /Users/$(USER)/homebrew/opt/readline/lib

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

