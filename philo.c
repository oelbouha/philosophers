/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:10:01 by oelbouha          #+#    #+#             */
/*   Updated: 2023/04/03 22:44:14 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(char **av)
{
	t_philosophers	p;
	int				ret;

	if (is_valid_argument(av))
	{
		printf("error\n");
		return ;
	}
	ret = check_argument(av, &p);
	if (ret == 1 || p.num_of_ph > 250)
	{
		printf("error\n");
		return ;
	}
	if (ret == 2)
		return ;
	create_threads(&p);
}

int	main(int c, char **av)
{
	if (c == 6 || c == 5)
		start(av);
	else
		return (1);
}
