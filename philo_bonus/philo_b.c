/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokanchik <bokanchik@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:29:20 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/18 19:31:12 by bokanchik        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

// initialiser et ouvrir un semaphore nomme (+etablie une connexion entre un sem et un processus)
// sem_t *sem_open(const char *name, int oflag);

// lock a sem, operation P
// int sem_wait(sem_t *sem); 
// prends le pointeur vers le sem a blocquer

// unlock a semaphore, operation V
// int sem_post(sem_t *sem);

int main(int ac, char **av)
{
	t_data_b	*data;
	
	if (ac < 5 || ac > 6)
		return (1);
	data = init_data_b(av, ac);
	if (!data)
		return (printf("Invalid argument.\n"), 1);
	create_children(data);
	parent_monitor(data);
	free_data_b(data);
	return (0);
}
