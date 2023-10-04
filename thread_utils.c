/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:12:35 by maskedduck        #+#    #+#             */
/*   Updated: 2022/01/21 17:11:05 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_write(__uint64_t start, char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->glob->ecrire);
	if (for_dead(philo, 0) == 1)
	{
		pthread_mutex_unlock(&philo->glob->ecrire);
		return ;
	}
	ft_putnbr(get_time() - start);
	write(1, "\t", 1);
	if (message[0] != 'T')
	{
		ft_putnbr(philo->position);
		write(1, " ", 1);
	}
	ft_putstr(message);
	if (message[0] == 'd' || message[0] == 'T')
		for_dead(philo, 1);
	pthread_mutex_unlock(&philo->glob->ecrire);
}

int	for_dead(t_philo *philo, int i)
{
	int	plop;

	pthread_mutex_lock(&philo->glob->lock_dead);
	if (i == 1)
	{
		philo->glob->dead = 1;
		pthread_mutex_unlock(&philo->glob->lock_dead);
		return (0);
	}
	else if (i == 0)
	{
		plop = philo->glob->dead;
		pthread_mutex_unlock(&philo->glob->lock_dead);
		return (plop);
	}
	pthread_mutex_unlock(&philo->glob->lock_dead);
	return (0);
}

void	after_meal(t_philo *philo, __uint64_t start)
{
	int	m;

	m = -1;
	pthread_mutex_unlock(philo->lfork);
	if (philo->glob->nphilo != 1)
		pthread_mutex_unlock(philo->rfork);
	philo_write(start, "is sleeping", philo);
	while (++m < 10)
	{
		if (for_dead(philo, 0) != 1)
			usleep(philo->tsleep * 100);
		else
			break ;
	}
	philo_write(start, "is thinking", philo);
	usleep(1000);
}

void	get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	philo_write(philo->start, "has taken a fork", philo);
	if (philo->glob->nphilo == 1)
		while (for_dead(philo, 0) != 1)
			usleep(100);
	else
		pthread_mutex_lock(philo->rfork);
	philo_write(philo->start, "has taken a fork", philo);
}
