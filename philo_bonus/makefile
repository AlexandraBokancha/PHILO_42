NAME			= philo_bonus

SRC				=  philo_b.c \
					init_data_b.c \
					end_clean_b.c \
					routine_b.c \
					utils_b.c \
					monitor_b.c \
					
OBJS			= ${SRC:.c=.o}

CC				=	cc

HEAD 			= -Iphilo_b.h

CFLAGS			= -Wall -Wextra -Werror -pthread -g3

all				:	${NAME}

%.o: %.c philo_b.h
	@${CC} ${CFLAGS} ${HEAD} -c $< -o $@

$(NAME)			:	${OBJS}	
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} 
	@echo "\nBONUS_PHILO AT THE TABLE\n"

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
