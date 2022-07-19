/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:37:28 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/19 14:52:27 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time_since_last(t_philo *philo, t_rules *rules)
{
	if (philo->last_meal != 0)
		return (get_time() - philo->last_meal);
	else
		return (get_time() - rules->first_time);
}

long	get_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
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