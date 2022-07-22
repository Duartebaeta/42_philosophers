/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:08:42 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 16:09:40 by duartebaeta      ###   ########.fr       */
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
	struct s_philo	*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	increment;
	pthread_mutex_t	death;
	pthread_mutex_t	meals_left;
} t_rules;

typedef struct s_philo
{
	int					id;
	int					left_fork_id;
	int					right_fork_id;
	long				last_meal;
	long				last_sleep_time;
	int					times_ate;
	struct s_rules		*rules;
	pthread_t			thread_id;
} t_philo;


long	get_time();
int		arg_checker(int argc, char **argv);
int		init_all(char **argv, t_rules *rules);
int		init_philo(t_rules *rules);
int		init_mut(t_rules *rules);
int		simulator(t_rules *rules);
void	print_big(char **big);
int		start_threads(t_rules *rules);
void *	start_simulation(void *r);
int		join_threads(t_rules *rules);
int		start_taking_forks(t_rules *rules, t_philo *philo);
int		start_eating(t_rules *rules, t_philo *philo);
int		check_time_eat(t_rules *rules, t_philo *philo);
long	get_time_since_last(t_philo *philo, t_rules *rules);
int		print_status(t_rules *rules, t_philo *philo, char *message);
long	get_simu_time(t_rules *rules);
int		release_fork(t_rules *rules, int fork_id);
int		send_to_die(t_rules *rules, t_philo *philo);
int		start_sleeping(t_rules *rules, t_philo *philo);
int		start_thinking(t_rules *rules, t_philo *philo);
int		release_both_forks(t_rules *rules, t_philo *philo);
long	get_time_until_death(t_rules *rules, t_philo *philo);
int		check_meals(t_rules *rules);
int		test_init(t_rules *rules);
int		destroy_mut(t_rules *rules);
int		free_mem(t_rules *rules);
void	anti_deadlock(t_rules *rules, t_philo *philo);

#endif