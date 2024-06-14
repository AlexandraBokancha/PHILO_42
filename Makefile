NAME			= philo	

RUN             = run

SRC				= main.c init.c utils.c routine.c checker.c end_clean.c print.c	\
				utils2.c

BONUS_PATH      = philo_bonus/

BONUS 			= utils.c \
					$(addprefix $(BONUS_PATH), philo_b.c init_data_b.c init_philo_b.c \
					utils_b.c utils2_b.c end_clean_b.c) \
				

OBJS			= ${SRC:.c=.o}

BONUS_OBJS      = $(BONUS:.c=.o)

CC				=	cc

BONUS_HEAD      = $(addprefix $(BONUS_PATH), philo_b.h)\

HEAD 			= -Iphilo.h

CFLAGS			= -Wall -Wextra -Werror -pthread -g3

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
	@rm -rf ${OBJS} $(BONUS_OBJS)

fclean			:	clean
	@rm -rf ${NAME}

re				:	fclean all

bonus				: $(BONUS_OBJS)
	@$(CC) $(CFLAGS) -I$(HEAD) -I$(BONUS_HEAD) $(BONUS_OBJS) -o $(NAME)
	@echo "\nBONUS PHILO AT THE TABLE\n"   

.PHONY			:	all clean fclean re bonus

run: $(BONUS_OBJS)
	clear && $(CC) $(CFLAGS) -I$(HEAD) -I$(BONUS_HEAD) $(BONUS_OBJS) $^ -o $(RUN)

ffclean: fclean
	rm -rf $(RUN)