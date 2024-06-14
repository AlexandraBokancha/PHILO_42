/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:56:52 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/14 19:30:05 by albokanc         ###   ########.fr       */
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

typedef struct s_sem_b
{
	sem_t			**forks; // les fourchettes qui sont au milieu de la table
	int				sem_val;
	char 			**sem_name;
}				t_sem_b;

typedef struct s_philo_b
{
    struct s_data_b	*data;
	struct s_sem_b *sems;
	pthread_t		tid; 
    int 			waiting; 
    
}              t_philo_b;

typedef struct s_data_b
{
	struct timeval	*tv;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
    int             nb_of_philo;
    int				nb_of_meals;
}                   t_data_b;


t_data_b	*init_data_b(char **av, int ac);
t_philo_b	*init_philo_b(t_data_b *data);
t_sem_b 	*init_sem_b(t_data_b *data);

int			is_digit(char **str);
int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
char		*ft_strdup(char *s);

void	close_sems(t_data_b *data, t_sem_b *sems);
void	free_data_b(t_data_b *data);

#endif