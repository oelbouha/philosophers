/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:58:38 by oelbouha          #+#    #+#             */
/*   Updated: 2023/02/27 19:58:40 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	is_valid_argument(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '+')
			{
				if (is_digit(&av[i][j + 1]))
					return (1);
			}
			else if (!ft_isdigit(av[i][j]))
				return (1);
		}
	}
	return (0);
}

int	check_argument(char **av, t_philosophers *p)
{
	p->num_of_ph = ft_atoi(av[1]);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		p->num_of_meals = ft_atoi(av[5]);
		if (p->num_of_meals == 0)
			return (2);
		if (p->num_of_meals < 0)
			return (1);
	}
	if (p->time_to_die < 0 || p->time_to_eat < 0 || p->time_to_sleep < 0
		|| p->num_of_ph < 0)
		return (1);
	return (0);
}
