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

void	is_sleeping(int id, int time_to_sleep)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %d is sleeping\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), id);
	usleep(time_to_sleep * 1000);
}

void	is_eating(int id, int time_to_eat)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %d has taken a fork\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), id);
	gettimeofday(&current_time, NULL);
	printf("%ld %d is eating\n", (current_time.tv_sec * 1000 +
		current_time.tv_usec / 1000), id);
	usleep(time_to_eat * 1000);
}

void	terminate_threads(t_philosophers *p)
{
	static int check;
	struct timeval	current_time;

	pthread_mutex_lock(p->c);
	gettimeofday(&current_time, NULL);
	usleep(100);
	check++;
	if (check == 2)
		printf("%ld %d is died\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
	pthread_mutex_unlock(p->c);
}

void	*routine(void *arg)
{
	t_philosophers *p = (t_philosophers *)arg;
	struct timeval	current_time;
	static long		count;
	static int		count_meals;
	static int		check;

	if (p->id % 2 == 0)
		usleep(30);
	count = p->count;
	while (1)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
		gettimeofday(&current_time, NULL);
		if ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - count > p->time_to_die)
			check = 1;
		if (check == 0 && p->id % 2)
			count = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		// printf("count ==> %ld\n", count);
		if (check == 0)
		{
			gettimeofday(&current_time, NULL);
			printf("%ld %d has taken a fork\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
			gettimeofday(&current_time, NULL);
			printf("%ld %d is eating\n", (current_time.tv_sec * 1000 +
				current_time.tv_usec / 1000), p->id);
			usleep(p->time_to_eat * 1000);
			// is_eating(p->id, p->time_to_eat);
			count_meals++;
		}
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		if (p->meals && (count_meals == p->meals * p->num_of_ph))
				check = 3;
		if (check == 0)
		{
			is_sleeping(p->id, p->time_to_sleep);
			if (check == 0)
			{
				gettimeofday(&current_time, NULL);
				printf("%ld %d is thinking\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
			}
		}
		if (check == 1)
			terminate_threads(p);
		if (check >= 1)
			return (0);
	}
	return (0);
}

void	create_threads(t_philosophers *p)
{
	pthread_t		th[p->num_of_ph];
	pthread_mutex_t	forks[p->num_of_ph];
	t_philosophers	philosophers[p->num_of_ph];
	struct timeval	current_time;
	pthread_mutex_t lock;
	int				i;
	int				j;

	pthread_mutex_init(&lock, NULL);
	j = -1;
	while (++j < p->num_of_ph)
		pthread_mutex_init(&forks[j], NULL);	
	i = -1;
	j = 0;
	gettimeofday(&current_time, NULL);
	while (++i < p->num_of_ph)
	{
		philosophers[i].id = i;
		philosophers[i].c = &lock;
		philosophers[i].count = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
		philosophers[i].left_fork = &forks[j];
		philosophers[i].right_fork = &forks[(j + 1) % p->num_of_ph];
		philosophers[i].meals = p->num_of_meals;
		philosophers[i].num_of_ph = p->num_of_ph;
		philosophers[i].time_to_die = p->time_to_die;
		philosophers[i].time_to_eat = p->time_to_eat;
		philosophers[i].time_to_sleep = p->time_to_sleep;
		if (pthread_create(th + i, NULL, &routine, &philosophers[i]) != 0)
			return ;
		j++;
	}
	i = -1;
	while (++i < p->num_of_ph)
		if (pthread_join(th[i], NULL) < 0)
			return ;
}

void	get_data(char **av)
{
	struct timeval current_time;
	t_philosophers	p;

	if (is_valid_argument(av))
	{
		printf("error\n");
		return ;
	}
	p.num_of_ph = ft_atoi(av[1]);
	p.time_to_die = ft_atoi(av[2]);
	p.time_to_eat = ft_atoi(av[3]);
	p.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		p.num_of_meals = ft_atoi(av[5]);
	if (p.num_of_ph == 1)
	{
		gettimeofday(&current_time, NULL);
		printf("%ld %d has taken a fork\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), 0);
		usleep(p.time_to_die * 1000);
		gettimeofday(&current_time, NULL);
		printf("%ld %d died\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), 0);
		return ;
	}
	if (p.time_to_die < 0 || p.time_to_eat < 0 || p.time_to_sleep < 0 || p.num_of_ph < 0)
	{
		printf("error\n");
		return ;
	}
	create_threads(&p);
}

int main(int c, char **av)
{
	if (c == 6 || c == 5)
		get_data(av);
	else
		return (1);
}
