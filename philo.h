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

/*			           structures
===========================================================
*/

typedef struct s_data
{
	struct timeval	current_time;
	int				count_meals;
}	t_data;

typedef struct s_philosophers
{
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		lock;
	struct timeval		current_time;
	pthread_mutex_t		*c;
	long				count;
	int					id;
	int					i;
	int					meals;
	int					count_meals;
	int					num_of_ph;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
}	t_philosophers;

/*		   	             functions
===========================================================
*/

int		ft_atoi(char *str);
int		ft_isdigit(int s);
int		is_valid_argument(char **av);
int		check_argument(char **av, t_philosophers *p);
void	wait_for_threads_to_fiish(t_philosophers *p, pthread_t *th);
void	init_mutex_forks(t_philosophers *p, pthread_mutex_t *forks);
void	one_philo(int time);
void	is_sleeping(int id, int time_to_sleep);
int		is_eating(int id, int time_to_eat);
void	is_thinking(int id);
void	create_threads(t_philosophers *p);
void	terminate_threads(t_philosophers *p);
void	manage_philosophers(t_philosophers *p, long time, t_data *data, int *check);

#endif