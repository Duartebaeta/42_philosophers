/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:39:08 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/20 16:50:32 by duartebaeta      ###   ########.fr       */
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
	while (1)
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

int	simulator(t_rules *rules)
{
	rules->first_time = get_time();
	start_threads(rules);
	join_threads(rules);
	if (check_meals(rules) == EXIT_SUCCESS)
		ft_printf("%s\n", "All philosophers have eaten enough meals");
	return (0);
}