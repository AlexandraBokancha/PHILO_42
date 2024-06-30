/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:57:03 by bokanchik         #+#    #+#             */
/*   Updated: 2024/06/30 21:17:23 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	think_b(t_data_b *data, int i)
{
	sem_wait(data->lock);
	printf("\033[0;33m%ld %i is thinking\033[0m\n", get_time_b(data), i + 1);
	sem_post(data->lock);
	if (i % 2 && data->t_to_eat >= data->t_to_sleep)
		usleep(((data->t_to_eat - data->t_to_sleep) * 1000) + 1000);
}

void	sleep_b(t_data_b *data, int i)
{
	sem_wait(data->lock);
	printf("\033[0;32m%ld %i is sleeping\033[0m\n", get_time_b(data), i + 1);
	sem_post(data->lock);
	ft_usleep_b(data, data->t_to_sleep);
}

void	eat_b(t_data_b *data, int i)
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
	sem_post(data->lock);
	sem_wait(data->lock);
	data->t_meal = get_time_b(data);
	data->meal_count += 1;
	sem_post(data->lock);
	ft_usleep_b(data, data->t_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_routine(int i, t_data_b *data)
{
	pthread_t	pid;

	data->philo_id = i;
	if (i % 2)
		ft_usleep_b(data, data->t_to_eat);
	pthread_create(&pid, NULL, is_dead, data);
	while (1)
	{
		eat_b(data, i);
		sleep_b(data, i);
		think_b(data, i);
	}
}

int	create_children(t_data_b *data)
{
	int	i;

	i = 0;
	data->pid = malloc(sizeof(pid_t) * (data->nb_of_philo));
	if (!data->pid)
		return (exit(1), printf("Malloc error\n"));
	start_b(data);
	while (i < data->nb_of_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			philo_routine(i, data);
		else if (data->pid[i] < 0)
		{
			printf("fork() error\n");
			close_sems(data);
			free_data_b(data);
			exit(1);
		}
		i++;
	}
	parent_monitor(data);
	return (0);
}
