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
	int i = -1;
	while (++i < 2)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
		printf("time xx %d  has taken a fork\n", p->id);
		printf("time xx %d  is eating\n", p->id);
		// sleep(2);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		printf("time xx %d  is thinking\n", p->id);
		// sleep(2);
		printf("time xx %d  is sleeping\n", p->id);
		// sleep(2);
	}
	return (NULL);
}


void	create_threads(t_data data)
{
	pthread_t		th[data.num_of_ph];
	pthread_mutex_t	forks[data.num_of_ph];
	t_philosophers	philosophers[data.num_of_ph];
	int				i;

	i = -1;
	while (++i < data.num_of_ph)
		pthread_mutex_init(&forks[i], NULL);
	
	i = -1;
	while (++i < data.num_of_ph)
	{
		philosophers[i].id = i;
		// if (i == data.num_of_ph - 1)
		// 	philosophers[i].left_fork = &forks[0];
		// else
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % data.num_of_ph];
		if (pthread_create(th + i, NULL, &routine, &philosophers[i]) != 0)
		{
			perror("philo");
			return ;
		}
	}
	i = -1;
	while (++i < data.num_of_ph)
	{
		if (pthread_join(th[i], NULL) < 0)
		{
			perror("philo");
			return ;
		}
	}
}

void	start(char **av)
{
	t_data	data;

	data.num_of_ph = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.num_of_meals = ft_atoi(av[5]);
	create_threads(data);
}

int main(int c, char **av)
{
	if (c >= 2)
		start(av);
	else
		return (1);
}