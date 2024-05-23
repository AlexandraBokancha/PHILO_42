/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:22:04 by albokanc          #+#    #+#             */
/*   Updated: 2024/05/09 14:19:33 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <stdio.h> // printf
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // thread's fuctions

// process data structure 

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		tid;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
	long int		t_meal;
	int				philo_nb;
	int				dead;
	int				full;
	int				count;
}				t_philo;

// input data structure

typedef struct s_data
{
	struct timeval	*tv;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_control;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_stop;
	long int		t_start;
	int				stop;
	int				nb_of_philo;
	int				nb_of_times_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
}				t_data;

// parsing 

int			ft_atoi(const char *nptr);
int			is_digit(char **str);

// initialization 

t_data		*init_data(char **av, int ac);
t_philo		*init_locks(t_data *data);
int			init_threads(t_philo *philos, t_data *data);
void		fill_data(t_data *data, char **av, int ac);

// routine

void		*thread_routine(void *data);
void		eating(t_philo *philo);
void		joining(t_philo *philo);
void		clean_all(t_philo *philo, t_data *data);
void		one_philo(t_philo *philo);

// print

void		print_fork(t_philo *philo);
void		print_eat(t_philo *philo);
void		print_sleep(t_philo *philo);
void		print_think(t_philo *philo);
void		print_dead(t_philo *philo);

// checker

int			death_status(t_philo *philo, int i, int run);
void		full_status(t_philo *philo);
void		set_dead(t_philo *philo);
void		death_checker(t_philo *philo);

// helpful functions

int			ft_usleep(t_data *data, size_t time);
void		start(t_data *data);
long int	get_time(t_data *data);

#endif
