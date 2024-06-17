/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:56:52 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/17 17:23:33 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "/home/albokanc/42/vogsphere/RANK03/philo_v1/philo.h"
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <stdio.h> // printf
# include <unistd.h> // write, usleep
# include <pthread.h> // thread's fuctions
# include <semaphore.h> // semaphore's functions
# include <fcntl.h>           
# include <sys/stat.h>  
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_data_b
{
	struct timeval	*tv;
	
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
    int             nb_of_philo;
    int				nb_of_meals;
	long int 		t_start;
	long int        t_meal;
	pid_t           *pid;
	char 			**name_tab;
	sem_t			**forks;
	sem_t           *lock;
	int             status;
	int				meal_count;
}                   t_data_b;


t_data_b	*init_data_b(char **av, int ac);

int			create_children(t_data_b *data);
void		parent_monitor(t_data_b *data);

int			is_digit_b(char **str);
int			ft_atoi_b(const char *nptr);
char		*ft_itoa(int n);

void		start_b(t_data_b *data);
long int	get_time_b(t_data_b *data);
int			ft_usleep_b(t_data_b *data, size_t time);

void	close_sems(t_data_b *data);
void	free_data_b(t_data_b *data);

#endif
