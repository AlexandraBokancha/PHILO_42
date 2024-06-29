/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:49:47 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/29 22:05:40 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead(t_philo *philo)
{
	u_int64_t	t;

	pthread_mutex_lock(&philo->data->m_meal);
	t = get_time(philo->data) - philo->t_meal;
	pthread_mutex_unlock(&philo->data->m_meal);
	if (t >= philo->data->time_to_die)
		//pthread_mutex_unlock(&philo->data->m_meal);
		return (0);
	return (1);
}

void	set_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_of_philo)
	{
		pthread_mutex_lock(&philo->data->m_stop);
		philo[i].dead = 1;
		pthread_mutex_unlock(&philo->data->m_stop);
		i++;
	}
}

int	is_full(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_of_philo)
	{
		if (philo[i].full == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

int	full_check(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->nb_of_times_to_eat <= 0)
		return (0);
	while (i < philo->data->nb_of_philo)
	{
		pthread_mutex_lock(&philo->data->m_meal);
		if (philo[i].count == philo->data->nb_of_times_to_eat)
		{	
			pthread_mutex_lock(&philo->data->m_stop);
			philo[i].full = 1;
			pthread_mutex_unlock(&philo->data->m_stop);
		}
		pthread_mutex_unlock(&philo->data->m_meal);
		i++;
	}
	if (is_full(philo) == 1)
		return (1);
	return (0);
}

void	death_checker(t_philo *philo)
{
	int	i;
	int	run;

	i = 0;
	run = 1;
	while (run)
	{
		while (i < philo->data->nb_of_philo)
		{
			if (!dead(&philo[i]))
			{
				run = death_status(philo, i, run);
				break ;
			}
			i++;
		}
		i = 0;
		if (full_check(philo) == 1)
		{
			full_status(philo);
			break ;
		}
		usleep(50);
	}
}
