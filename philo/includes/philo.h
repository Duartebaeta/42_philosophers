/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:08:42 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/04 20:38:41 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "../libft/libft.h"
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_rules
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				opt_eat;
	int				died;
	long			first_time;
	struct s_philo	philos[250];
	pthread_mutex_t	forks[250];
	pthread_mutex_t	eating;
	pthread_mutex_t	writing;
} t_rules;

typedef struct s_philo
{
	int					id;
	int					left_fork_id;
	int					right_fork_id;
	long				last_meal;
	int					times_ate;
	struct s_rules		*rules;
	pthread_t			thread_id;
} t_philo;


long	get_time();
int	arg_checker(int argc, char **argv);
int	init_all(char **argv, t_rules *rules);
int	init_philo(t_rules *rules);
int	init_mut(t_rules *rules);

#endif