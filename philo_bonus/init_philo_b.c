/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:27:22 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/14 19:31:44 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"


t_philo_b	*init_philo_b(t_data_b *data)
{
	t_philo_b	*philo;
	int			i;
	
	i = 0;
	philo = malloc(sizeof(t_philo_b) * data->nb_of_philo);
	if (!philo)
		return (NULL);
	while (i < data->nb_of_philo)
	{
		philo[i].data = data;
		i++;
	}
	return (philo);
}
