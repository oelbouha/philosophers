/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:55:50 by oelbouha          #+#    #+#             */
/*   Updated: 2023/02/28 12:55:52 by oelbouha         ###   ########.fr       */
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

void	one_philo(int time)
{
	printf("%ld %d has taken a fork\n", get_time(), 0);
	ft_usleep(time, get_time());
	printf("%ld %d died\n", get_time(), 0);
}

void	is_sleeping(int id, int time_to_sleep)
{
	printf("%ld %d is sleeping\n", get_time(), id);
	ft_usleep(time_to_sleep, get_time());
}

int	is_eating(int id, int time_to_eat, t_philosophers *p)
{
	static int			count_meals;

	usleep(100);
	printf("%ld %d has taken a fork\n", get_time(), id);
	printf("%ld %d is eating\n", get_time(), id);
	ft_usleep(time_to_eat, get_time());
	
	pthread_mutex_lock(p->lock);
	pthread_mutex_lock(p->eat);
	count_meals++;
	p->count_meals = count_meals;
	pthread_mutex_unlock(p->eat);
	pthread_mutex_unlock(p->lock);
	return (0);
}
