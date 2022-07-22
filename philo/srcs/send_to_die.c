/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:29:10 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 15:38:36 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	send_to_die(t_rules *rules, t_philo *philo)
{
	usleep(get_time_until_death(rules, philo) * 1000);
	if (print_status(rules, philo, "is dead") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&rules->death);
	rules->died = 1;
	pthread_mutex_unlock(&rules->death);
	// exit(0);
	return (EXIT_SUCCESS);
}