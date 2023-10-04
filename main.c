/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eydupray <eydupray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:20:54 by eydupray          #+#    #+#             */
/*   Updated: 2022/01/21 17:11:01 by eydupray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void	*philo2)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo2;
	i = 0;
	while (for_dead(philo, 0) != 1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->tdeath < get_time() - philo->lmeal)
		{
			philo_write(philo->start, "died", philo);
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		else if (philo->neat == 0)
		{
			philo_write(philo->start, "Tout les philosophes ont mange", philo);
			pthread_mutex_unlock(&philo->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(2000);
		i = (i + 1) % philo->glob->nphilo;
	}
	return (NULL);
}

void	break_routine(t_philo *philo)
{
	int	m;

	while (for_dead(philo, 0) != 1)
	{
		m = -1;
		get_fork(philo);
		pthread_mutex_lock(&philo->mutex);
		philo->lmeal = get_time();
		philo->neat--;
		philo_write(philo->start, "is eating", philo);
		while (++m < 10)
		{
			if (for_dead(philo, 0) != 1)
				usleep(philo->teat * 100);
			else
				break ;
		}
		pthread_mutex_unlock(&philo->mutex);
		after_meal(philo, philo->start);
	}
}

void	*start_routine(void *philo2)
{
	t_philo		*philo;
	pthread_t	tid2;

	philo = (t_philo *)philo2;
	philo->start = get_time();
	philo->lmeal = philo->start;
	pthread_create(&tid2, 0, check_death, (void *)philo);
	break_routine(philo);
	pthread_join(tid2, NULL);
	return (NULL);
}

void	start_thread(t_glob *glob)
{
	int			i;
	pthread_t	*tid;

	i = 0;
	tid = malloc(sizeof(pthread_t) * glob->nphilo);
	if (!tid)
		return ;
	while (i < glob->nphilo)
	{
		pthread_create(&tid[i], 0, start_routine, (void *)&glob->philo[i]);
		i++;
	}
	i = 0;
	while (i < glob->nphilo)
		pthread_join(tid[i++], NULL);
	free(tid);
}

int	main(int ac, char **av)
{
	t_glob	glob;

	if (ac < 5 || ac > 6)
		return (0);
	ft_init(av, &glob);
	mutex_init(&glob);
	ft_init_philo(&glob);
	start_thread(&glob);
	free(glob.philo);
	free(glob.forks);
}
