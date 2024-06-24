/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:57:03 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/24 19:59:06 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void think_b(t_data_b *data, int i)
{
    sem_wait(data->lock);
    printf("\033[0;33m%ld %i is thinking\033[0m\n", get_time_b(data), i + 1);
    sem_post(data->lock);
    // peutetre enleve la condiiton se i%2
	if (i % 2 && data->t_to_eat >= data->t_to_sleep)
		usleep(((data->t_to_eat - data->t_to_sleep) * 1000) + 1000);
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
	sem_wait(data->lock);
	printf("%ld %i has taken a fork\n", get_time_b(data), i + 1);
   	sem_post(data->lock);
	sem_wait(data->forks);
	sem_wait(data->lock);
	printf("%ld %i has taken a fork\n", get_time_b(data), i + 1);
	sem_post(data->lock);
	sem_wait(data->lock);
    printf("\033[0;34m%ld %i is eating\033[0m\n", get_time_b(data), i + 1);
    data->t_meal = get_time_b(data);
    data->meal_count += 1;
	sem_post(data->lock);
    ft_usleep_b(data, data->t_to_eat); 
	sem_post(data->forks);
	sem_post(data->forks);
}
void	*is_dead(void *data)
{
	t_data_b	*data_b;
	long int    t;

	data_b = (t_data_b *)data;
	while (1)
	{
		sem_wait(data_b->lock);
		t = get_time_b(data) - data_b->t_meal;
		if (t >= data_b->t_to_die)
		{
			printf("\033[0;31m%ld %i died\033[0m\n", get_time_b(data), data_b->philo_id + 1);
            exit (0) ;
		}
		sem_post(data_b->lock);
	}
	ft_usleep_b(data_b, 200);
    return (NULL);
}

void    philo_routine(int i, t_data_b *data)
{
	pthread_t	pid;
	
	data->philo_id = i;
	if (i % 2)
		ft_usleep_b(data, data->t_to_sleep / data->nb_of_philo);
	pthread_create(&pid, NULL, is_dead, data);
    while (1)
    {
        if (data->nb_of_meals != -1 && data->meal_count >= data->nb_of_meals)
            break;
        eat_b(data, i);
        sleep_b(data, i);
        think_b(data, i);
    }
}

int create_children(t_data_b *data)
{
    int i;
	
    i = 0;
	start_b(data);
    data->pid = malloc(sizeof(pid_t) * (data->nb_of_philo));
    if (!data->pid)
    	return (1);
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
	parent_monitor(data); 
    return (0);
}
