/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:08 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 14:38:49 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *	start_simulation(void *r)
{
	t_rules	*rules;
	t_philo	*philo;
	static int	counter = 0;

	rules = (t_rules *)r;
	pthread_mutex_lock(&rules->increment);
	philo = &rules->philos[counter++];
	pthread_mutex_unlock(&rules->increment);
	while (1 && check_meals(rules) != EXIT_SUCCESS)
	{
		if (start_taking_forks(rules, philo) == EXIT_FAILURE)
			break ;
		if (start_eating(rules, philo) == EXIT_FAILURE)
			break;
		if (start_sleeping(rules, philo) == EXIT_FAILURE)
			break;
		if (start_thinking(rules, philo) == EXIT_FAILURE)
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

int	destroy_mut(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	if (pthread_mutex_destroy(&rules->increment) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&rules->death) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&rules->meals_left) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	free_mem(t_rules *rules)
{
	free(rules->forks);
	free(rules->philos);
	free(rules->threads);
	free(rules);
	return (EXIT_SUCCESS);
}

int	simulator(t_rules *rules)
{
	rules->first_time = get_time();
	start_threads(rules);
	join_threads(rules);
	if (check_meals(rules) == EXIT_SUCCESS && rules->opt_eat != -1)
		ft_printf("%s\n", "All philosophers have eaten enough meals");
	destroy_mut(rules);
	free_mem(rules);
	return (0);
}