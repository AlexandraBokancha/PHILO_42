/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:11:59 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/14 19:12:45 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

char	*set_sem_name(int i)
{
	char *sem_num;
	char *name;
	
	sem_num = ft_itoa(i + 1);
	name = ft_strjoin("sem", sem_num);
	free(sem_num);
	return (name);
}

t_sem_b *init_sem_b(t_data_b *data)
{
	t_sem_b *sems;
	int i;

	i = 0;
	sems = malloc(sizeof(t_sem_b));
	if (!sems)
		return (NULL);
	sems->sem_val = 1; 
	sems->forks = malloc(sizeof(sem_t *) * data->nb_of_philo);
	if (!sems->forks)
		return (NULL);
	sems->sem_name = malloc(sizeof(char *) * data->nb_of_philo);
	if (!sems->sem_name)
		return (NULL);
	while (i < data->nb_of_philo)
	{
		sems->sem_name[i] = set_sem_name(i);
		sems->forks[i] = sem_open(sems->sem_name[i], O_CREAT, 0644, sems->sem_val);
		if (sems->forks[i] == SEM_FAILED)
			exit (1);
		i++;
	}
	return (sems);
}

void	fill_data_b(t_data_b *data, char **av, int ac)
{
	int i;

	i = 0;
	data->nb_of_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->nb_of_meals = ft_atoi(av[5]);
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
	if (!is_digit(av))
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
