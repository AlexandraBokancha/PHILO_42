/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:05:52 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/14 17:08:31 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (!dup)
		return (NULL);
	while (s[i])
	{	
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
