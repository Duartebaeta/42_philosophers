/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:21:46 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 16:09:58 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_aloc(t_rules *rules)
{
	rules->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (1);
	rules->philos = (t_philo *)malloc(sizeof(t_philo) * rules->n_philo);
	if (!rules->philos)
		return (2);
	rules->threads = (pthread_t *)malloc(sizeof(pthread_t) * rules->n_philo);
	if (!rules->threads)
		return (3);
	return (0);
}

int	init_mut(t_rules *rules)
{
	int i;

	i = rules->n_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->death), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->increment), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meals_left), NULL))
		return (1);
	return (0);
}

void	anti_deadlock(t_rules *rules, t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->left_fork_id = philo->id;
		philo->right_fork_id = (philo->id + 1) % rules->n_philo;
	}
	else
	{
		philo->left_fork_id = (philo->id + 1) % rules->n_philo;
		philo->right_fork_id = philo->id;
	}
}

int	init_philo(t_rules *rules)
{
	int i;

	i = rules->n_philo;
	while (--i >= 0)
	{
		rules->philos[i].id = i;
		if (rules->philos[i].id % 2)
		{
			rules->philos[i].left_fork_id = rules->philos[i].id;
			rules->philos[i].right_fork_id = (rules->philos[i].id + 1) % rules->n_philo;
		}
		else
		{
			rules->philos[i].left_fork_id = (rules->philos[i].id + 1) % rules->n_philo;
			rules->philos[i].right_fork_id = rules->philos[i].id;
		}
		rules->philos[i].times_ate = 0;
		rules->philos[i].last_meal = 0;
		rules->philos[i].last_sleep_time = 0;
		rules->philos[i].rules = rules;
	}
	return (0);
}

int	init_all(char **argv, t_rules *rules)
{
	rules->died = 0;
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->opt_eat = ft_atoi(argv[5]);
	else
		rules->opt_eat = -1;
	if (rules->n_philo < 2 || rules->time_die < 0 || rules->time_eat < 0 || rules->time_sleep < 0)
		return (1);
	if (init_aloc(rules))
		return (3);
	if (init_mut(rules))
		return (2);
	init_philo(rules);
	return (0);
}

int	test_init(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		printf("Philo %d, left-id: %d right-id: %d\n", rules->philos[i].id, rules->philos[i].left_fork_id, rules->philos[i].right_fork_id);
		i++;
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_rules	*rules;

	if (arg_checker(argc, argv))
		return (2);
	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (3);
	if (init_all(argv, rules))
		return (4);
	simulator(rules);
	return 0;
}
