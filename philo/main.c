/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:02:22 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/29 17:18:58 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (0);
	data = init_data(av, ac);
	if (!data)
	{	
		printf("Invalid argument.\n");
		return (0);
	}
	philo = init_locks(data);
	if (data->nb_of_philo == 1)
	{	
		one_philo(philo);
		clean_all(philo, data);
		return (0);
	}
	if (init_threads(philo, data) == 0)
		death_checker(philo);
	joining(philo);
	clean_all(philo, data);
	return (0);
}
