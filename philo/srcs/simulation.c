/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:08 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/19 15:05:34 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_time_eat(t_rules *rules, t_philo *philo)
{
	if (rules->time_die <= rules->time_eat  || rules->time_die <= get_time_since_last(philo, rules))
		return (EXIT_FAILURE);
	else if (rules->n_philo == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_taking_forks(t_rules *rules, t_philo *philo)
{
	if (check_time_eat(rules, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("Philo %d is at forks\n", philo->id);
	return (EXIT_SUCCESS);
}

int	start_eating(t_philo *philo)
{
	printf("Philo %d is eating\n", philo->id);
	return(EXIT_SUCCESS);
}

void *	start_simulation(void *r)
{
	t_rules	*rules;
	t_philo	*philo;
	static int	counter = 0;

	rules = (t_rules *)r;
	pthread_mutex_lock(&rules->increment);
	philo = &rules->philos[counter++];
	pthread_mutex_unlock(&rules->increment);
	while (1 && rules->died == 0)
	{
		if (start_taking_forks(rules, philo) == EXIT_FAILURE)
		{
			pthread_mutex_lock(&rules->writing);
			rules->died = 1;
			printf("Philo %d died\n", philo->id);
			pthread_mutex_unlock(&rules->writing);
			break ;
		}
		if (start_eating(philo) == EXIT_FAILURE)
			break;
	}
	return (NULL);
}

int	start_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_create(&(rules->threads[i]), NULL, start_simulation, (void *)rules);
		i++;
	}
	return 0;
}

int	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_join(rules->threads[i], NULL);
		i++;
	}
	return 0;
}

int	simulator(t_rules *rules)
{
	rules->first_time = get_time();
	start_threads(rules);
	join_threads(rules);
	return (0);
}