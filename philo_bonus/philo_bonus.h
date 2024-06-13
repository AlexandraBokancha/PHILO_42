/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:56:52 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/13 22:41:29 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <stdio.h> // printf
# include <unistd.h> // write, usleep
# include <pthread.h> // thread's fuctions

typedef struct s_philo_b
{
    struct s_data_b *data;
    int waiting; 
    
}              t_philo_b;

typedef struct s_data_b
{
    int             *sem_forks;
    int             philo_nb;
    int				nb_of_meals;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
}                   t_data_b;

