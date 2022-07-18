/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duartebaeta <duartebaeta@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:37:28 by duartebaeta       #+#    #+#             */
/*   Updated: 2022/07/04 20:38:00 by duartebaeta      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	arg_checker(int argc, char **argv)
{
	int	counter;

	if (argc != 5 && argc != 6)
		return (1);
	while (*argv)
	{
		counter = 0;
		while (*argv[counter])
		{
			if (ft_isdigit(ft_atoi(*argv[counter])))
				counter++;
			else
				return (1);
		}
		argv++;
	}
	return (0);
}