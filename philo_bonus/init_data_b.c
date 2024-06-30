/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:11:59 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/30 20:57:00 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

sem_t	*init_sem_fork(t_data_b *data)
{
	sem_t	*sem_f;

	sem_unlink("/fork");
	sem_f = sem_open("/fork", O_CREAT, 0644, data->nb_of_philo);
	if (sem_f == SEM_FAILED)
	{
		printf("sem_open() error\n");
		free_data_b(data);
		exit(1);
	}
	return (sem_f);
}

sem_t	*init_sem_lock(t_data_b *data)
{
	sem_t	*sem_l;

	sem_unlink("/lock");
	sem_l = sem_open("/lock", O_CREAT, 0644, 1);
	if (sem_l == SEM_FAILED)
	{
		printf("sem_open() error\n");
		sem_close(data->forks);
		free_data_b(data);
		exit(1);
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
	data->lock = init_sem_lock(data);
	data->meal_count = 0;
	data->t_meal = 0;
	data->t_start = 0;
	data->dead = 0;
	if (ac == 6)
	{
		data->nb_of_meals = ft_atoi_b(av[5]);
		if (data->nb_of_meals <= 0)
			return (free(data), close_sems(data));
	}
	else
		data->nb_of_meals = -1;
}

t_data_b	*init_data_b(char **av, int ac)
{
	t_data_b	*data;

	data = malloc(sizeof(t_data_b));
	if (!data)
		exit(1);
	if (!is_digit_b(av))
		fill_data_b(data, av, ac);
	else
		return (free(data), NULL);
	if (data->nb_of_philo <= 0 || data->nb_of_philo > 200 || data->t_to_die <= 0
		|| data->t_to_eat <= 0 || data->t_to_sleep <= 0)
		return (close_sems(data), free(data), NULL);
	data->tv = malloc(sizeof(struct timeval));
	if (!data->tv)
	{
		close_sems(data);
		free_data_b(data);
		exit(1);
	}
	return (data);
}
