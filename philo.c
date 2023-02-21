/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:10:01 by oelbouha          #+#    #+#             */
/*   Updated: 2023/02/13 20:10:02 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosophers *p = (t_philosophers *)arg;
	struct timeval current_time;
	useconds_t	t_to_eat;
	useconds_t	t_to_sleep;

	t_to_eat = p->time_to_eat * 1000;
	t_to_sleep = p->time_to_sleep * 1000;
	int i = 0;
	while (++i <= 2)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
		gettimeofday(&current_time, NULL);
		printf("%ld %d  has taken a fork\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
		gettimeofday(&current_time, NULL);
		printf("%ld %d  is eating\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
		usleep(t_to_eat);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		gettimeofday(&current_time, NULL);
		printf("%ld %d  is sleeping\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
		usleep(t_to_sleep);
		gettimeofday(&current_time, NULL);
		printf("%ld %d  is thinking\n", (current_time.tv_sec * 1000 + current_time.tv_usec / 1000), p->id);
	}
	return (NULL);
}


void	create_threads(t_philosophers *p)
{
	pthread_t		th[p->num_of_ph];
	pthread_mutex_t	forks[p->num_of_ph];
	t_philosophers	philosophers[p->num_of_ph];
	int				i;

	i = -1;
	while (++i < p->num_of_ph)
		pthread_mutex_init(&forks[i], NULL);	
	// printf("meals ---> %d\n", p->num_of_meals);
	// printf("sleep ---> %d\n", p->time_to_sleep);
	// printf("time to die ---> %d\n", p->time_to_die);
	i = 0;
	int j = 0;
	while (++i <= p->num_of_ph)
	{
		philosophers[i].id = i;
		philosophers[i].left_fork = &forks[j];
		philosophers[i].meals = p->num_of_meals;
		philosophers[i].time_to_die = p->time_to_die;
		philosophers[i].time_to_eat = p->time_to_eat;
		philosophers[i].time_to_sleep = p->time_to_sleep;
		philosophers[i].right_fork = &forks[(j + 1) % p->num_of_ph];
		if (pthread_create(th + i, NULL, &routine, &philosophers[i]) != 0)
		{
			perror("philo");
			return ;
		}
		j++;
	}
	i = -1;
	while (++i < p->num_of_ph)
	{
		if (pthread_join(th[i], NULL) < 0)
		{
			perror("philo");
			return ;
		}
	}
}

void	get_data(char **av)
{
	t_philosophers	p;

	p.num_of_ph = ft_atoi(av[1]);
	p.time_to_die = ft_atoi(av[2]);
	p.time_to_eat = ft_atoi(av[3]);
	p.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		p.num_of_meals = ft_atoi(av[5]);
	create_threads(&p);
}

int main(int c, char **av)
{
	if (c == 6 || c == 5)
		get_data(av);
	else
		return (1);
}