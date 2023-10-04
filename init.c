/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:48:09 by eydupray          #+#    #+#             */
/*   Updated: 2022/01/17 18:12:18 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(char **av, t_glob *glob)
{
	glob->nphilo = ft_atoi(av[1]);
	glob->tdeath = ft_atoi(av[2]);
	glob->teat = ft_atoi(av[3]);
	glob->tsleep = ft_atoi(av[4]);
	if (av[5] != 0)
		glob->neat = ft_atoi(av[5]);
	else
		glob->neat = -2;
	glob->dead = 0;
}

void	mutex_init(t_glob *glob)
{
	int	i;

	i = 0;
	glob->forks = malloc(sizeof(pthread_mutex_t) * glob->nphilo);
	while (i < glob->nphilo)
	{
		pthread_mutex_init(&glob->forks[i], 0);
		i++;
	}
	pthread_mutex_init(&glob->ecrire, 0);
	pthread_mutex_init(&glob->lock_dead, 0);
}

void	fork_swap(t_philo *philo)
{
	pthread_mutex_t	*tmp;

	tmp = NULL;
	tmp = philo->lfork;
	philo->lfork = philo->rfork;
	philo->rfork = tmp;
}

void	ft_init_philo(t_glob *glob)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = NULL;
	philo = malloc(sizeof(t_philo) * glob->nphilo);
	if (!philo)
		exit_and_free();
	while (i < glob->nphilo)
	{
		philo[i].position = i + 1;
		philo[i].tdeath = (__uint64_t)glob->tdeath;
		philo[i].rfork = &(glob->forks[i]);
		philo[i].lfork = &(glob->forks[(i + 1) % glob->nphilo]);
		if (philo[i].position % 2 == 1)
			fork_swap(&philo[i]);
		philo[i].glob = glob;
		philo[i].neat = glob->neat + 1;
		philo[i].teat = glob->teat;
		philo[i].tsleep = glob->tsleep;
		philo[i].lmeal = 0;
		pthread_mutex_init(&philo[i].mutex, 0);
		i++;
	}
	glob->philo = philo;
}
