
SRCS	= ft_memset.c     ft_bzero.c     ft_memcpy.c     ft_memccpy.c    ft_memmove.c ft_memchr.c  ft_memcmp.c  \
		  ft_isalpha.c    ft_isdigit.c   ft_isalnum.c    ft_isascii.c    ft_isprint.c ft_toupper.c ft_tolower.c \
		  ft_strlen.c     ft_strchr.c    ft_strrchr.c    ft_strncmp.c    ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
		  ft_atoi.c       ft_atold.c	 ft_calloc.c     ft_strdup.c	 ft_realloc.c	   						\
		  ft_substr.c     ft_strjoin.c   ft_strtrim.c    ft_split.c      ft_itoa.c    ft_strmapi.c              \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c											\
		  ft_power.c	  ft_isspace.c	 ft_strcmp.c	 ft_strchr_end.c ft_swap.c	  ft_strapp.c

SRCS_B	= ft_lstnew.c  ft_lstadd_front.c ft_lstsize.c   ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		  ft_lstiter.c ft_lstmap.c       ft_lstcreate.c

SRCS_GNL= get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}
OBJS_GNL= ${SRCS_GNL:.c=.o}

GNL_DIR	= get_next_line/
NAME	= libft.a
AR		= ar rc
RM		= rm -f

.c.o:
			gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} ${OBJS_B} $(addprefix ${GNL_DIR}, ${OBJS_GNL})
			@echo "\033[95m\nCompiling libft 🤓...\033[0m"
			${AR} ${NAME} ${OBJS} ${OBJS_B} $(addprefix ${GNL_DIR}, ${OBJS_GNL})
			ranlib ${NAME}

clean:
			${MAKE} only_clean

only_clean:
			@echo "\033[91m\nclean libft 🐙 \033[0m"
			${RM} ${OBJS} ${OBJS_B} $(addprefix ${GNL_DIR}, ${OBJS_GNL})

fclean:		only_clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re

