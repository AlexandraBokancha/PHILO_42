/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:57:03 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/18 20:30:15 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

// DES SEMAPHORES POUR LE PRINT 

int check_last_meal(t_data_b *data)
{
    long int    t;

    sem_wait(data->lock);
    t = get_time_b(data) - data->t_meal;
    sem_post(data->lock);
    if (t >= data->t_to_die)
        return (1);
    return (0);
}

void think_b(t_data_b *data, int i)
{
    sem_wait(data->lock);
    printf("\033[0;33m%ld %i is thinking\033[0m\n", get_time_b(data), i + 1);
    sem_post(data->lock);
}

void sleep_b(t_data_b *data, int i)
{
    sem_wait(data->lock);
    printf("\033[0;32m%ld %i is sleeping\033[0m\n", get_time_b(data), i + 1);
    sem_post(data->lock);
    ft_usleep_b(data, data->t_to_sleep);
}

void    eat_b(t_data_b *data, int i)
{	
	sem_wait(data->forks);
	printf("%ld %i has taken a fork\n", get_time_b(data), i + 1);
	sem_wait(data->forks);
    printf("\033[0;34m%ld %i is eating\033[0m\n", get_time_b(data), i + 1);
    sem_wait(data->lock);
    data->t_meal = get_time_b(data);
    data->meal_count += 1;
   	sem_post(data->lock);
    ft_usleep_b(data, data->t_to_eat); 
	sem_post(data->forks);
	sem_post(data->forks);
}


void    philo_routine(int i, t_data_b *data)
{
    while (1)
    {
        if (data->nb_of_meals != -1 && data->meal_count >= data->nb_of_meals)
            break;
        if (check_last_meal(data))
        {
            sem_wait(data->lock);
            printf("\033[0;31m%ld %i died\033[0m\n", get_time_b(data), i + 1);
            exit (1);
        }
        eat_b(data, i);
        sleep_b(data, i);
        think_b(data, i);
    }
}

int create_children(t_data_b *data)
{
    int i;
	
    i = 0;
    data->meal_count = 0;
    data->t_meal = 0;
    data->t_start = -1;
    data->pid = malloc(sizeof(pid_t) * (data->nb_of_philo));
    if (!data->pid)
    	return (1);
    start_b(data);
    while (i < data->nb_of_philo)
    {
        data->pid[i] = fork();
        if (data->pid[i] == 0)
        {
			philo_routine(i, data);
            exit(0);
        }
        else if (data->pid[i] < 0)
        {
            printf("fork() error\n");
            exit (1);
        }
        i++;
    } 
    return (0);
}
