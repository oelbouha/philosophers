/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:10:01 by oelbouha          #+#    #+#             */
/*   Updated: 2023/02/23 14:35:33 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating(int id, int time_to_eat)
{
	struct timeval current_time;
	static int 	count_meals;

	gettimeofday(&current_time, NULL);
	printf("%ld %d has taken a fork\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), id);
	gettimeofday(&current_time, NULL);
	printf("%ld %d is eating\n", (current_time.tv_sec * 1000 +
		current_time.tv_usec / 1000), id);
	usleep(time_to_eat * 1000);
	count_meals++;
	return (count_meals);
}

void	func(int *check, t_philosophers *p, int *count_meals)
{
	// struct timeval	current_time;

	// if (*check == 0 && (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - *count > p->time_to_die)
	// 	*check = 1;
	// if (*check == 0 && p->id % 2)
	// 	*count = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (*check == 0)
		*count_meals = is_eating(p->id, p->time_to_eat);
	if (*count_meals == p->meals * p->num_of_ph)
		*check = 3;
}

int	manage_philo(t_philosophers *p, long time, t_data *data)
{
	static int		check;
	static long	count;

	count = time;
	while (1)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
		gettimeofday(&data->current_time, NULL);
		if (check == 0 && (data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000) - count > p->time_to_die)
			check = 1;
		if (check == 0 && p->id % 2)
			count = data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000;
		func(&check, p, &data->count_meals);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		if (check == 0)
			is_sleeping(p->id, p->time_to_sleep);
		gettimeofday(&data->current_time, NULL);
		if (check == 0)
			printf("%ld %d is thinking\n", (data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000), p->id);
		if (check != 0)
			break ;
	}
	return (check);
}

void	*routine(void *arg)
{
	t_philosophers *p = (t_philosophers *)arg;
	static int		check;
	t_data			data;

	if (p->id % 2 == 0)
		usleep(50);
	while (1)
	{
		if (check == 0)
			check = manage_philo(p, p->count, &data);
		if (check == 1)
			terminate_threads(p);
		if (check >= 1)
			return (0);
	}
	return (0);
}

void	init_mutex_and_forks(t_philosophers *p, pthread_mutex_t *forks)
{
	int i;

	i = -1;
	while (++i < p->num_of_ph)
		pthread_mutex_init(&forks[i], NULL);
}

void	wait_for_threads_to_fiish(t_philosophers *p, pthread_t *th)
{
	int i;

	i = -1;
	while (++i < p->num_of_ph)
		if (pthread_join(th[i], NULL) < 0)
			return ;
}

void	create_threads(t_philosophers *p)
{
	t_philosophers	philosophers[p->num_of_ph];
	pthread_t		th[p->num_of_ph];
	pthread_mutex_t forks[p->num_of_ph];

	p->i = -1;
	p->j = 0;
	init_mutex_and_forks(p, forks);
	pthread_mutex_init(&p->lock, NULL);
	gettimeofday(&p->current_time, NULL);
	while (++p->i < p->num_of_ph)
	{
		philosophers[p->i].id = p->i;
		philosophers[p->i].c = &p->lock;
		philosophers[p->i].count = p->current_time.tv_sec * 1000 + p->current_time.tv_usec / 1000;
		philosophers[p->i].left_fork = &forks[p->j];
		philosophers[p->i].right_fork = &forks[(p->j++ + 1) % p->num_of_ph];
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

void	init(char **av)
{
	t_philosophers	p;
	int				ret;

	if (is_valid_argument(av))
	{
		printf("error\n");
		return ;
	}
	ret = check_argument(av, &p);
	if (ret == 1)
	{
		printf("error\n");
		return ;
	}
	if (ret == 2)
		return ;
	if (p.num_of_ph == 1)
	{
		one_philo(p.time_to_die);
		return ;
	}
	create_threads(&p);
}

int main(int c, char **av)
{
	if (c == 6 || c == 5)
		init(av);
	else
		return (1);
}
