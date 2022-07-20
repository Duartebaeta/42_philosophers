/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:07:09 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/20 16:03:28 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_eating(t_rules *rules, t_philo *philo)
{
	if(get_time_since_last(philo, rules) >= rules->time_die)
	{
		send_to_die(rules, philo);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(&rules->meals_left);
	philo->times_ate++;
	pthread_mutex_unlock(&rules->meals_left);
	philo->last_meal = get_simu_time(rules);
	if (print_status(rules, philo, "is eating") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	usleep(rules->time_eat * 1000);
	release_both_forks(rules, philo);
	return(EXIT_SUCCESS);
}

int	start_sleeping(t_rules *rules, t_philo *philo)
{
	if(rules->time_sleep >= rules->time_die)
	{
		send_to_die(rules, philo);
		return (EXIT_FAILURE);
	}
	if (print_status(rules, philo, "is sleeping") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	usleep(rules->time_sleep * 1000);
	return(EXIT_SUCCESS);
}

int	start_thinking(t_rules *rules, t_philo *philo)
{
	if (print_status(rules, philo, "is thinking") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}