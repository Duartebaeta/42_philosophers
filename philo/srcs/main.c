/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:21:46 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/04 20:37:57 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mut(t_rules *rules)
{
	int i;

	i = rules->n_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->eating), NULL))
		return (1);
	return (0);
}

int	init_philo(t_rules *rules)
{
	int i;

	i = rules->n_philo;
	while (--i >= 0)
	{
		rules->philos[i].id = i;
		rules->philos[i].left_fork_id = i;
		rules->philos[i].right_fork_id = (i + 1) % rules->n_philo;
		rules->philos[i].times_ate = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].rules = rules;
	}
	return (0);
}

int	init_all(char **argv, t_rules *rules)
{
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->opt_eat = ft_atoi(argv[5]);
	else
		rules->opt_eat = -1;
	if (rules->n_philo < 2 || rules->time_die < 0 || rules->time_eat < 0 || rules->time_sleep < 0 || rules->n_philo > 250)
		return (1);
	if (init_mut(rules))
		return (1);
	init_philo(rules);
	return (0);
	
}

int main(int argc, char **argv)
{
	t_rules	*rules;

	if (arg_checker(argc, argv))
		return (2);
	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (3);
	return 0;
}
