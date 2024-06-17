/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:57:03 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/17 19:24:12 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void think_b(t_data_b *data, int i)
{
    printf("\033[0;33m%ld %i is thinking\033[0m\n", get_time_b(data), i);
    usleep(((data->t_to_eat - data->t_to_sleep) * 1000) + 1000);
}

void sleep_b(t_data_b *data, int i)
{
    printf("\033[0;32m%ld %i is sleeping\033[0m\n", get_time_b(data), i);
    ft_usleep_b(data, data->t_to_sleep);
}

void    eat_b(t_data_b *data, int i, sem_t **sem_child, sem_t *sem_lock)
{
    sem_wait(sem_child[i - 1]);
	printf("%ld %i has taken a first fork\n", get_time_b(data), i);
	sem_wait(sem_child[(i) % data->nb_of_philo]);  
    printf("\033[0;34m%ld %i is eating\033[0m\n", get_time_b(data), i);
    sem_wait(sem_lock);
    data->t_meal = get_time_b(data);
    data->meal_count += 1;
    sem_post(sem_lock);
    ft_usleep_b(data, data->t_to_eat); 
	sem_post(sem_child[i - 1]);
	sem_post(sem_child[(i) % data->nb_of_philo]);  

}
int check_last_meal(t_data_b *data, sem_t *sem_lock)
{
    long int    t;

    sem_wait(sem_lock);
    t = get_time_b(data) - data->t_meal;
    sem_post(sem_lock);
    if (t >= data->t_to_die)
        return (1);
    sem_post(sem_lock);
    return (0);
}


void    philo_routine(int i, t_data_b *data)
{
    sem_t **sem_child;
    sem_t *sem_lock;
	int id;

	id = 0;
	sem_child = NULL;
    data->meal_count = 0;
    data->t_meal = 0;
	sem_child = malloc(sizeof(sem_t *) * (data->nb_of_philo + 1));
	if (!sem_child)
		return ;
    while (id < data->nb_of_philo)
	{
		sem_child[id] = sem_open(data->name_tab[id], 0);	
    	if (sem_child[id] == SEM_FAILED)
   	 	{
			printf("sem_open() error\n");
			exit (1);
   		}
		id++;
	}
    sem_lock = sem_open("/lock", 0);
    if (sem_lock == SEM_FAILED)
    {
        printf("sem_open() error\n");
		exit (1);
    }
    while (1)
    {
        if (data->nb_of_meals != -1 && data->meal_count >= data->nb_of_meals)
            break;
        if (check_last_meal(data, sem_lock))
        {
            printf("\033[0;31m%ld %i died\033[0m\n", get_time_b(data), i);
			break;
        }
        eat_b(data, i, sem_child, sem_lock);
        sleep_b(data, i);
        think_b(data, i);
    }
	id = 0;
	while (id < data->nb_of_philo)
	{
		sem_close(sem_child[id]);
		id++;
	}
	sem_close(sem_lock);
}

int create_children(t_data_b *data)
{
    int i;
	
    i = 0;
    data->pid = malloc(sizeof(pid_t) * (data->nb_of_philo + 1));
    if (!data->pid)
    	return (1);
    while (i < data->nb_of_philo)
    {
    	start_b(data);
        data->pid[i] = fork();
        if (data->pid[i] == 0)
        {
			philo_routine(i + 1, data);
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
