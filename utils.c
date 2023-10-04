/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:46:21 by eydupray          #+#    #+#             */
/*   Updated: 2022/01/21 17:02:23 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((__uint64_t)time.tv_sec * 1000 + ((__uint64_t)time.tv_usec) / 1000);
}

int	is_valid(char c, long int nb, long int neg)
{
	if ((ft_is_in(c, "0123456789") == 0))
		return (0);
	if (neg == 1)
	{
		if (nb <= 214748364 && 2147483647 - nb * 10 >= c - '0')
			return (1);
	}
	else
		if (nb <= 214748364 && 2147483648 - nb * 10 >= c - '0')
			return (1);
	return (0);
}

void	exit_and_free(void)
{
	write(2, "Error\n", 6);
	exit(0);
}

int	ft_is_in(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
