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

void	terminate_threads(t_philosophers *p)
{
	static int		check;
	struct timeval	current_time;

	pthread_mutex_lock(p->c);
	gettimeofday(&current_time, NULL);
	usleep(100);
	check++;
	if (check == 1)
		printf("%ld %d is died\n", (current_time.tv_sec * 1000
				+ current_time.tv_usec / 1000), p->id);
	pthread_mutex_unlock(p->c);
}

void	one_philo(int time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %d has taken a fork\n", (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000), 0);
	usleep(time * 1000);
	gettimeofday(&current_time, NULL);
	printf("%ld %d died\n", (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000), 0);
}

void	is_sleeping(int id, int time_to_sleep)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %d is sleeping\n", (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000), id);
	usleep(time_to_sleep * 1000);
}

void	is_thinking(int id)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %d is thinking\n", (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000), id);
}

int	is_eating(int id, int time_to_eat)
{
	struct timeval	current_time;
	static int		count_meals;

	gettimeofday(&current_time, NULL);
	printf("%ld %d has taken a fork\n", (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000), id);
	gettimeofday(&current_time, NULL);
	printf("%ld %d is eating\n", (current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000), id);
	usleep(time_to_eat * 1000);
	count_meals++;
	return (count_meals);
}
