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

void	eat_and_count_meals(int *check, t_philosophers *p, int *count_meals)
{
	if (*check == 0)
		*count_meals = is_eating(p->id, p->time_to_eat);
	if (*count_meals == p->meals * p->num_of_ph)
		*check = 3;
}

void	manage_philosophers(t_philosophers *p, long time, t_data *data, int *check)
{
	static long		count;

	count = time;
	while (1)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
		gettimeofday(&data->current_time, NULL);
		if (*check == 0 && (data->current_time.tv_sec * 1000
				+ data->current_time.tv_usec / 1000) - count > p->time_to_die)
			*check = 1;
		if (*check == 0 && p->id % 2)
			count = data->current_time.tv_sec * 1000
				+ data->current_time.tv_usec / 1000;
		eat_and_count_meals(check, p, &data->count_meals);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		if (*check == 0)
			is_sleeping(p->id, p->time_to_sleep);
		if (*check == 0)
			is_thinking(p->id);
		if (*check != 0)
			break ;
	}
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

int	main(int c, char **av)
{
	if (c == 6 || c == 5)
		init(av);
	else
		return (1);
}
