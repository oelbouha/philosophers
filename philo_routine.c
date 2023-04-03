/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:55:50 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/03 22:44:25 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time_to_sleep, long start)
{
	while (1)
	{
		if (get_time() - start >= time_to_sleep)
			break ;
		usleep(200);
	}
}

void	is_sleeping(int id, int time_to_sleep, t_philosophers *p)
{
	pthread_mutex_lock(p->eat);
	printf("%ld %d is sleeping\n", get_time(), id);
	pthread_mutex_unlock(p->eat);
	ft_usleep(time_to_sleep, get_time());
}

void	is_eating(int id, int time_to_eat, t_philosophers *p)
{
	static int			count_meals;

	pthread_mutex_lock(p->eat);
	printf("%ld %d is eating\n", get_time(), id);
	pthread_mutex_unlock(p->eat);
	ft_usleep(time_to_eat, get_time());
	pthread_mutex_lock(p->eat);
	count_meals++;
	p->count_meals = count_meals;
	pthread_mutex_unlock(p->eat);
}
