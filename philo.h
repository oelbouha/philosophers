/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:10:08 by oelbouha          #+#    #+#             */
/*   Updated: 2023/02/13 20:10:10 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>


/*			    structures
==========================================*
*/

typedef struct s_philosophers
{
	pthread_mutex_t 	*left_fork;
	pthread_mutex_t 	*right_fork;
	pthread_mutex_t 	*c;
	long				count;
	int					id;
	int					meals;
	int					num_of_ph;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
}	t_philosophers;

/*		   	      utils
=========================================*
*/
int	ft_atoi(char *str);

#endif