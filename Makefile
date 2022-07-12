NAME			=	philo
HEADERS			=	philo.h
CC				= 	gcc
RM				= 	rm -rf
CFLAGS 			= 	-g -Wall -Wextra -Werror -pthread #-fsanitize=address
AR				= 	ar rcs

SRCS	=	main.c	\
			parsing.c \
			utils.c \

OBJS	= ${SRCS:.c=.o}

LIBS 	= -L ./libft -lft

COMPIL = ${CC} ${CFLAGS} ${LIBS} -o $

MAKE_EXT	= @make -s --no-print-directory -C

$(NAME):	${OBJS}
			$(MAKE_EXT) ./libft
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

bonus:		${OBJS_B}
			$(MAKE_EXT) ./libft
			@${COMPIL}

clean:
		${MAKE_EXT} ./libft clean
		${RM} ${OBJS} ${OBJS_B}

fclean: clean
		${MAKE_EXT} ./libft fclean
		${RM} ${NAME} ${NAME_CHK}

re:		fclean all

.PHONY:	all clean fclean re bonus