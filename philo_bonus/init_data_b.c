/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:11:59 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/16 11:46:25 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

// After the semaphore named name has been created by sem_open() 
// with the O_CREAT flag, other processes can connect to the semaphore
// by calling sem_open() with the same value of name.

sem_t	*init_sem_fork(t_data_b *data)
{
	
	data->forks = malloc(sizeof(sem_t) * data->nb_of_philo);
	if (!data->forks)
		return (NULL);
	data->forks = sem_open("/fork", O_CREAT, 0644, data->nb_of_philo);
	if (data->forks == SEM_FAILED)
	{
		printf("sem_open() error\n");
		exit (1);
	}
	return (data->forks);
}

sem_t *init_sem_lock(t_data_b *data)
{
	data->lock = malloc(sizeof(sem_t) * 2);
	if (!data->lock)
		return (NULL);
	data->lock = sem_open("/lock", O_CREAT, 0644, 1);
	if (!data->lock)
	{
		printf("sem_open() error\n");
		exit (1);
	}
	return (data->lock);
}

void	fill_data_b(t_data_b *data, char **av, int ac)
{
	data->nb_of_philo = ft_atoi_b(av[1]);
	data->t_to_die = ft_atoi_b(av[2]);
	data->t_to_eat = ft_atoi_b(av[3]);
	data->t_to_sleep = ft_atoi_b(av[4]);
	data->forks = init_sem_fork(data);
	data->lock = init_sem_lock(data);
	if (ac == 6)
	{
		data->nb_of_meals = ft_atoi_b(av[5]);
		if (data->nb_of_meals <= 0)
			return (free(data));
	}
	else
		data->nb_of_meals = -1;
}

t_data_b	*init_data_b(char **av, int ac)
{
	t_data_b	*data;

	data = malloc(sizeof(t_data_b));
	if (!data)
		return (NULL);
	if (!is_digit_b(av))
		fill_data_b(data, av, ac);
	else
		return (free(data), NULL);
	if (data->nb_of_philo <= 0 || data->nb_of_philo > 200 \
		|| data->t_to_die <= 0 || data->t_to_eat <= 0 \
		|| data->t_to_sleep <= 0)
		return (free(data), NULL);
	data->tv = malloc(sizeof(struct timeval));
	if (!data->tv)
		return (NULL);
	return (data);
}
