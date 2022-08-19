NAME			=	philo_bonus
HEADERS			=	philo.h
CC				= 	gcc
RM				= 	rm -rf
CFLAGS 			= 	-g -Wall -Wextra -Werror -pthread #-fsanitize=address

SRC	=	main.c	\
		parsing.c \
		utils.c \
		routine.c 

OBJS	= ${SRC:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

bonus:	all

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re