/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:37:28 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/22 15:27:15 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time_until_death(t_rules *rules, t_philo *philo)
{
	long	time_elapsed;

	time_elapsed = get_simu_time(rules) - philo->last_meal;
	return (rules->time_die - time_elapsed);
}

long	get_time_since_last(t_philo *philo, t_rules *rules)
{
	if (philo->last_meal != 0)
		return (get_simu_time(rules) - philo->last_meal);
	else
		return (get_simu_time(rules) - rules->first_time);
}

long	get_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	get_simu_time(t_rules *rules)
{
	return (get_time() - rules->first_time);
}

int	arg_checker(int argc, char **argv)
{
	int	counter;
	int	subcounter;

	if (argc != 5 && argc != 6)
		return (1);
	counter = 1;
	while (argv[counter])
	{
		subcounter = 0;
		while (argv[counter][subcounter])
		{
			if (ft_isdigit(argv[counter][subcounter]))
				subcounter++;
			else
				return (2);
		}
		counter++;
	}
	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (3);
	return (0);
}

void	print_big(char **big)
{
	int	counter;

	counter = 0;
	while (big[counter])
	{
		ft_printf("%s\n", big[counter]);
		counter++;
	}
}

int	check_meals(t_rules *rules)
{
	int	i;

	i = 0;
	if (rules->opt_eat == -1)
		return (EXIT_FAILURE);
	while (i < rules->n_philo)
	{
		if (rules->philos[i].times_ate < rules->opt_eat)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	print_status(t_rules *rules, t_philo *philo, char *message)
{
	pthread_mutex_lock(&rules->death);
	if (rules->died == 1 || check_time_eat(rules, philo) == EXIT_FAILURE)
	{
		pthread_mutex_unlock(&rules->meals_left);
		pthread_mutex_unlock(&rules->death);
		return (EXIT_FAILURE);
	}
	printf("%s %d %s\n", ft_itoa(get_simu_time(rules)), philo->id, message);
	pthread_mutex_unlock(&rules->death);
	return (EXIT_SUCCESS);
}
