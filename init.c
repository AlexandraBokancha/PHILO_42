/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:01:07 by albokanc          #+#    #+#             */
/*   Updated: 2024/05/09 15:00:45 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char **av, int ac)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->stop = 0;
	if (is_digit(av) != 1)
		fill_data(data, av, ac);
	else
		return (free(data), NULL);
	if (data->nb_of_philo <= 0 || data->nb_of_philo > 200
		|| data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (free(data), NULL);
	data->tv = malloc(sizeof(struct timeval));
	if (!data->tv)
		return (NULL);
	return (data);
}

int	init_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	start(data);
	pthread_mutex_lock(&philo->data->m_stop);
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, thread_routine, &philo[i]))
		{
			printf("Error while creating thread.\n");
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->m_stop);
	return (0);
}

void	init_flags(t_philo *philo, int i)
{
	philo->dead = 0;
	philo->full = 0;
	philo->count = 0;
	philo->t_meal = 0;
	philo->philo_nb = (i + 1);
}

int	init_controls(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_time, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_control, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_stop, NULL))
		return (1);
	return (0);
}

t_philo	*init_locks(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	if (init_controls(data))
		return (NULL);
	philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!philo)
		return (0);
	while (i < data->nb_of_philo)
	{	
		init_flags(&philo[i], i);
		if (i != 0)
			philo[i].l_fork = &philo[i - 1].r_fork;
		pthread_mutex_init(&philo[i].r_fork, NULL);
		philo[i].data = data;
		i++;
	}
	philo[0].l_fork = &philo[data->nb_of_philo - 1].r_fork;
	return (philo);
}
