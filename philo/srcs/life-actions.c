/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:07:09 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 16:22:51 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_eating(t_rules *rules, t_philo *philo)
{
	if(get_time_since_last(philo, rules) >= rules->time_die)
	{
		release_both_forks(rules, philo);
		send_to_die(rules, philo);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(&rules->meals_left);
	philo->times_ate++;
	pthread_mutex_unlock(&rules->meals_left);
	philo->last_meal = get_simu_time(rules);
	if (print_status(rules, philo, "is eating") == EXIT_FAILURE)
	{
		release_both_forks(rules, philo);
		return (EXIT_FAILURE);
	}
	while (get_simu_time(rules) - philo->last_meal < rules->time_eat)
	{
		if (rules->died == 1)
		{
			release_both_forks(rules, philo);
			return (EXIT_FAILURE);
		}
	}
	release_both_forks(rules, philo);
	return(EXIT_SUCCESS);
}

int	start_sleeping(t_rules *rules, t_philo *philo)
{
	if(rules->time_sleep >= rules->time_die || rules->time_sleep >= get_time_until_death(rules, philo))
	{
		send_to_die(rules, philo);
		return (EXIT_FAILURE);
	}
	if (print_status(rules, philo, "is sleeping") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->last_sleep_time = get_simu_time(rules);
	while (get_simu_time(rules) - philo->last_sleep_time < rules->time_sleep)
	{
		if (rules->died == 1)
			return (EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}

int	start_thinking(t_rules *rules, t_philo *philo)
{
	if (print_status(rules, philo, "is thinking") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}