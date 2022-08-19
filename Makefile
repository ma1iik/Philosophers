NAME			=	phil
NAME_BONUS		=	philo_bonus
HEADERS			=	inc/philo.h
CC				= 	gcc
RM				= 	rm -rf
CFLAGS 			= 	-g -Wall -Wextra -Werror -pthread #-fsanitize=address
AR				= 	ar rcs

SRCS	=	src/main.c	\
			src/parsing.c \
			src/utils.c \
			src/routine.c \

SRC_BONUS	=	philo_bonus/main.c	\
				philo_bonus/parsing.c \
				philo_bonus/utils.c \
				philo_bonus/routine.c \

OBJS	= ${SRCS:.c=.o}

OBJS	= ${SRCS_BONUS:.c=.o}

#LIBS 	= -L ./libft -lft

COMPIL = ${CC} ${CFLAGS} -o $ #${LIBS}

MAKE_EXT	= @make -s --no-print-directory -C

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

bonus:		${OBJS_BONUS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME_BONUS}

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
		${RM} ${NAME} ${NAME_BONUS}

re:		fclean all

.PHONY:	all clean fclean re bonus