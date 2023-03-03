/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:04:59 by oelbouha          #+#    #+#             */
/*   Updated: 2023/03/02 12:05:00 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	static int		check;
	t_data			data;
	t_philosophers	*p;

	p = (t_philosophers *)arg;
	if (p->id % 2 == 0)
		usleep(50);
	while (1)
	{
		if (check == 0)
			manage_philosophers(p, p->count, &data, &check);
		if (check == 1)
			terminate_threads(p);
		if (check >= 1)
			return (NULL);
	}
	return (NULL);
}

void	create_threads(t_philosophers *p)
{
	t_philosophers		philosophers[256];
	pthread_t			th[256];
	pthread_mutex_t		forks[256];

	p->i = -1;
	init_mutex_forks(p, forks);
	pthread_mutex_init(&p->lock, NULL);
	gettimeofday(&p->current_time, NULL);
	while (++p->i < p->num_of_ph)
	{
		philosophers[p->i].id = p->i;
		philosophers[p->i].c = &p->lock;
		philosophers[p->i].count = p->current_time.tv_sec * 1000
			+ p->current_time.tv_usec / 1000;
		philosophers[p->i].left_fork = &forks[p->i];
		philosophers[p->i].right_fork = &forks[(p->i + 1) % p->num_of_ph];
		philosophers[p->i].meals = p->num_of_meals;
		philosophers[p->i].num_of_ph = p->num_of_ph;
		philosophers[p->i].time_to_die = p->time_to_die;
		philosophers[p->i].time_to_eat = p->time_to_eat;
		philosophers[p->i].time_to_sleep = p->time_to_sleep;
		if (pthread_create(th + p->i, NULL, &routine, &philosophers[p->i]) != 0)
			return ;
	}
	wait_for_threads_to_fiish(p, th);
}
