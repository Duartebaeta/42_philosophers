/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_release_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:08:23 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 15:57:41 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_time_eat(t_rules *rules, t_philo *philo)
{
	if (rules->time_die <= rules->time_eat  || get_time_since_last(philo, rules) >= rules->time_die || rules->n_philo == 1)
	{
		send_to_die(rules, philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	first_fork(t_rules *rules, t_philo *philo)
{
	if (pthread_mutex_lock(&rules->forks[philo->left_fork_id]) != EXIT_SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	if (print_status(rules, philo, "has taken a fork") == EXIT_FAILURE)
	{
		pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	second_fork(t_rules *rules, t_philo *philo)
{
	if (pthread_mutex_lock(&rules->forks[philo->right_fork_id]) != EXIT_SUCCESS)
	{
		release_fork(rules, philo->left_fork_id);
		return (EXIT_FAILURE);
	}
	if (print_status(rules, philo, "has taken a fork") == EXIT_FAILURE)
	{
		release_both_forks(rules, philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	release_fork(t_rules *rules, int fork_id)
{
	if (pthread_mutex_unlock(&rules->forks[fork_id]) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	release_both_forks(t_rules *rules, t_philo *philo)
{
	if (release_fork(rules, philo->left_fork_id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (release_fork(rules, philo->right_fork_id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_taking_forks(t_rules *rules, t_philo *philo)
{
	if (check_time_eat(rules, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (first_fork(rules, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (second_fork(rules, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}