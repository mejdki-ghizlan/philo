/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:28:06 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:28:10 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_valid_arg(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	if (str[i] == '-')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	get_args(char **av, t_table *table)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!is_valid_arg(av[i]))
			return (1);
		i++;
	}
	table->num_of_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->n_times_must_eat = ft_atol(av[5]);
	else
		table->n_times_must_eat = -1;
	if (table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->time_to_sleep <= 0 || table->num_of_philo <= 0
		|| table->num_of_philo > 200 || (av[5] && ft_atol(av[5]) <= 0))
		return (1);
	return (0);
}
