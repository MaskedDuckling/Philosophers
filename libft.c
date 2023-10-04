/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:49:41 by eydupray          #+#    #+#             */
/*   Updated: 2022/01/19 14:37:17 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	long int	neg;

	i = 0;
	res = 0;
	neg = 1;
	if (!str)
		exit_and_free();
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			exit_and_free();
	while (str[i])
	{
		if (!is_valid(str[i], res, neg))
			exit_and_free();
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}

void	ft_putnbr(int nb)
{
	char			c;
	unsigned int	b;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = nb * -1;
	}
	b = nb;
	if (b >= 10)
	{
		ft_putnbr(b / 10);
	}
	c = b % 10 + 48;
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
	write(1, "\n", 1);
}
