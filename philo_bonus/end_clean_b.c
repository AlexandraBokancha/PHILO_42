/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_clean_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:22:46 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/14 19:26:41 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	close_sems(t_data_b *data, t_sem_b *sems)
{
	int i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		sem_close(sems->forks[i]);
		sem_unlink(sems->sem_name[i]);
		free(sems->sem_name[i]);
		i++;
	}
	free(sems->sem_name);
	free(sems->forks);
	free(sems);
}

void	free_data_b(t_data_b *data)
{
	free(data->tv);
	free(data);
}

