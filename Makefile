NAME			=	philo
HEADERS			=	inc/philo.h
CC				= 	gcc
RM				= 	rm -rf
CFLAGS 			= 	-g -Wall -Wextra -Werror -pthread #-fsanitize=address
AR				= 	ar rcs

SRCS	=	src/main.c	\
			src/parsing.c \
			src/utils.c \
			src/routine.c \

OBJS	= ${SRCS:.c=.o}

#LIBS 	= -L ./libft -lft

COMPIL = ${CC} ${CFLAGS} -o $ #${LIBS}

MAKE_EXT	= @make -s --no-print-directory -C

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS} ${OBJS_B}

fclean: clean
		${RM} ${NAME} ${NAME_CHK}

re:		fclean all

.PHONY:	all clean fclean re bonus