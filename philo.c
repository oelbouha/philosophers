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
		if (check == 0)
		{
			is_eating(p->id, p->time_to_eat);
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
