/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:29:20 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/28 17:49:05 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	main(int ac, char **av)
{
	t_data_b	*data;

	if (ac < 5 || ac > 6)
		return (1);
	data = init_data_b(av, ac);
	if (!data)
		return (free(data), printf("Invalid argument.\n"), 1);
	create_children(data);
	free_data_b(data);
	return (0);
}
