/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:04:59 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/03 22:44:04 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval		current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	*routine(void *arg)
{
	t_philosophers		*p;

	p = (t_philosophers *)arg;
	if (p->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(p->eat);
		printf("%ld %d is thinking\n", get_time(), p->id);
		pthread_mutex_unlock(p->eat);
		pthread_mutex_lock(p->left_fork);
		printf("%ld %d has taken a fork\n", get_time(), p->id);
		pthread_mutex_lock(p->right_fork);
		printf("%ld %d has taken a fork\n", get_time(), p->id);
		pthread_mutex_lock(p->eat);
		p->count = get_time();
		pthread_mutex_unlock(p->eat);
		is_eating(p->id, p->time_to_eat, p);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		is_sleeping(p->id, p->time_to_sleep, p);
	}
	return (NULL);
}

int	check_death(t_philosophers *philo, t_philosophers *p)
{
	int	i;

	i = -1;
	while (1)
	{
		pthread_mutex_lock(p->eat);
		if (get_time() - philo[++i].count >= p->time_to_die)
		{
			printf("%ld %d is died\n", get_time(), philo[i].id);
			return (1);
		}
		if (philo[i].count_meals == p->num_of_ph * p->num_of_meals
			&& p->num_of_meals)
			return (1);
		pthread_mutex_unlock(p->eat);
		if (i == p->num_of_ph - 1)
			i = -1;
	}
	return (0);
}

void	create_threads(t_philosophers *p)
{
	t_philosophers		philos[255];
	pthread_t			th[255];
	pthread_mutex_t		forks[255];

	p->i = -1;
	init_mutex_forks(p, forks);
	while (++p->i < p->num_of_ph)
	{
		philos[p->i].id = p->i;
		philos[p->i].eat = p->eat;
		philos[p->i].count_meals = 0;
		philos[p->i].count = get_time();
		philos[p->i].left_fork = &forks[p->i];
		philos[p->i].right_fork = &forks[(p->i + 1) % p->num_of_ph];
		philos[p->i].time_to_eat = p->time_to_eat;
		philos[p->i].time_to_sleep = p->time_to_sleep;
		if (pthread_create(th + p->i, NULL, &routine, &philos[p->i]) != 0)
			return ;
	}
	p->i = -1;
	if (check_death(philos, p))
		while (++p->i < p->num_of_ph)
			pthread_detach(th[p->i]);
	destroy_mutex(p, forks);
}
