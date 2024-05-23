NAME			= philo	

SRC				= main.c init.c utils.c routine.c checker.c end_clean.c print.c	\
				utils2.c

OBJS			=	${SRC:.c=.o}

CC				=	cc

HEAD 			= -Iphilo.h

CFLAGS			= -Wall -Wextra -Werror -pthread -g3 -O2 -fsanitize=thread

all				:	${NAME}

%.o: %.c philo.h
	@${CC} ${CFLAGS} ${HEAD} -c $< -o $@

$(NAME)			:	${OBJS}	
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} 
	@echo "\nPHILO AT THE TABLE\n"

##val :	 ${NAME}
##		valgrind \
##		--tool=helgrind \
##		--tool=drd \
##		--leak-check=full \
##		--show-reachable=yes \
##		--show-leak-kinds=all ./${NAME}

clean			:
	@rm -rf ${OBJS}

fclean			:	clean
	@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re 
