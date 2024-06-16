/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:57:03 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/16 13:16:35 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void think_b(t_data_b *data, int *i)
{
    printf("\033[0;33m%ld %i is thinking\033[0m\n", get_time_b(data), *i);
    usleep(((data->t_to_eat - data->t_to_sleep) * 1000) + 1000);
}

void sleep_b(t_data_b *data, int *i)
{
    printf("\033[0;32m%ld %i is sleeping\033[0m\n", get_time_b(data), *i);
    ft_usleep_b(data, data->t_to_sleep);
}

void    eat_b(t_data_b *data, int *i, sem_t *sem_child, sem_t *sem_lock)
{
    sem_wait(sem_child); // 1er fourchette
    printf("%ld %i has taken a fork\n", get_time_b(data), *i);
    sem_wait(sem_child); // 2em fourchette
    printf("\033[0;34m%ld %i is eating\033[0m\n", get_time_b(data), *i);
    sem_wait(sem_lock);
    data->t_meal = get_time_b(data);
    data->meal_count += 1;
    sem_post(sem_lock);
    ft_usleep_b(data, data->t_to_eat);
    sem_post(sem_child);
    sem_post(sem_child);
        
}
int check_last_meal(t_data_b *data, sem_t *sem_lock)
{
    long int    t;

    sem_wait(sem_lock);
    t = get_time_b(data) - data->t_meal;
    if (t >= data->t_to_die)
    {
        sem_post(sem_lock);
        return (1);
    }
    sem_post(sem_lock);
    return (0);
}


void    philo_routine(int *i, t_data_b *data)
{
    sem_t *sem_child;
    sem_t *sem_lock;

    data->meal_count = 0;
    data->t_meal = 0;
    data->died = 0;
    sem_child = sem_open("/fork", 0);
    if (sem_child == SEM_FAILED)
    {
        printf("sem_open() error\n");
		exit (1);
    }
    sem_lock = sem_open("/lock", 0);
    if (sem_lock == SEM_FAILED)
    {
        printf("sem_open() error\n");
		exit (1);
    }
    *i+=1;
    while (1)
    {
        if (data->nb_of_meals != -1 && data->meal_count >= data->nb_of_meals)
            break;
        if (check_last_meal(data, sem_lock))
        {
            // dead_child
            printf("\033[0;31m%ld %i died\033[0m\n", get_time_b(data), *i);
            break;
        }
        eat_b(data, i, sem_child, sem_lock);
        sleep_b(data, i);
        think_b(data, i);
        sem_close(sem_child);
        sem_close(sem_lock);
    }
}

int create_children(t_data_b *data)
{
    int i;

    i = 0;
    data->pid = malloc(sizeof(pid_t) * data->nb_of_philo);
    if (!data->pid)
        return (1);
    start_b(data);
    while (i < data->nb_of_philo)
    {
        data->pid[i] = fork();
        if (data->pid[i] == 0)
        {
            philo_routine(&i, data);
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
