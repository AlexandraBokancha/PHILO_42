/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:11:59 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/18 18:59:21 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

// After the semaphore named name has been created by sem_open() 
// with the O_CREAT flag, other processes can connect to the semaphore
// by calling sem_open() with the same value of name.

sem_t	*init_sem_fork(t_data_b *data)
{
	sem_t *sem_f;

	sem_unlink("/fork");
	sem_f = sem_open("/fork", O_CREAT, 0644, data->nb_of_philo);
	if (sem_f == SEM_FAILED)
	{
		printf("sem_open() error\n");
		exit (1);
	}
	return (sem_f);
}

sem_t *init_sem_lock(void)
{
	sem_t *sem_l;

	sem_unlink("/lock");
	sem_l = sem_open("/lock", O_CREAT, 0644, 1);
	if (!sem_l)
	{
		printf("sem_open() error\n");
		exit (1);
	}
	return (sem_l);
}

void	fill_data_b(t_data_b *data, char **av, int ac)
{
	data->nb_of_philo = ft_atoi_b(av[1]);
	data->t_to_die = ft_atoi_b(av[2]);
	data->t_to_eat = ft_atoi_b(av[3]);
	data->t_to_sleep = ft_atoi_b(av[4]);
	data->forks = init_sem_fork(data);
	data->lock = init_sem_lock();
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

