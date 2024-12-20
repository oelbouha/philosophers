/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:41:22 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/03 22:44:37 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int s)
{
	if (!(s >= '0' && s <= '9'))
		return (0);
	else
		return (1);
}

void	init_mutex_forks(t_philosophers *p, pthread_mutex_t *forks)
{
	int		i;

	p->eat = malloc(sizeof(pthread_mutex_t));
	if (!p->eat)
		return ;
	pthread_mutex_init(p->eat, NULL);
	i = -1;
	while (++i < p->num_of_ph)
		pthread_mutex_init(&forks[i], NULL);
}

void	destroy_mutex(t_philosophers *p, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < p->num_of_ph)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(p->eat);
	free(p->eat);
}

long	ft_atoi(char *str)
{
	unsigned long	res;
	int				sign;
	int				i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		i++;
	}
	res *= sign;
	if (res > INT_MAX)
		return (-1);
	return (res);
}
