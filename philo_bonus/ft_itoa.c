/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:18:25 by albokanc          #+#    #+#             */
/*   Updated: 2024/06/17 17:23:41 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	find_len_int(long int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{	
		nbr *= -1;
		count += 1;
	}
	while (nbr > 0)
	{	
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

char	*putnbr(long int nbr, char *str, int len)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{	
		nbr *= -1;
		str[i] = '-';
		i++;
	}
	if (nbr < 10)
	{
		str[i] = nbr + '0';
		return (str);
	}
	while (len > i)
	{	
		len--;
		str[len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	nbr;

	nbr = n;
	len = find_len_int(nbr);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	str = putnbr(nbr, str, len);
	return (str);
}

