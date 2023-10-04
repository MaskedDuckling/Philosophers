/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maskedduck <maskedduck@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:22:34 by eydupray          #+#    #+#             */
/*   Updated: 2022/01/17 18:14:13 by maskedduck       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_glob	t_glob;

typedef struct s_philo
{
	int				position;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	mutex;
	__uint64_t		tdeath;
	t_glob			*glob;
	int				neat;
	int				teat;
	int				tsleep;
	__uint64_t		lmeal;
	__uint64_t		start;
}				t_philo;

typedef struct s_glob
{
	int				nphilo;
	int				tdeath;
	int				teat;
	int				tsleep;
	int				neat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_dead;
	int				dead;
	pthread_mutex_t	ecrire;
}				t_glob;

/*Init*/
void		ft_init_philo(t_glob *glob);
void		mutex_init(t_glob *glob);
void		ft_init(char **av, t_glob *glob);

/*Utils*/
int			ft_is_in(char c, char *s);
int			is_valid(char c, long int nb, long int neg);
int			ft_atoi(const char *str);
void		exit_and_free(void);
void		ft_putnbr(int nb);
void		ft_putstr(char *str);

/*Thread_utils*/
void		get_fork(t_philo *philo);
void		after_meal(t_philo *philo, __uint64_t start);
void		philo_write(__uint64_t start, char *message, t_philo *philo);
__uint64_t	get_time(void);
int			for_dead(t_philo *philo, int i);

#endif