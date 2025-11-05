/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:29:03 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:29:06 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (exit_error("mutex init failed"));
		i++;
	}
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->checker_death, NULL);
	pthread_mutex_init(&table->time_mutex, NULL);
	pthread_mutex_init(&table->dead_mutex, NULL);
	return (0);
}

int	init_data(t_table *table)
{
	int	i;

	table->philosopher = malloc(sizeof(t_philo) * table->num_of_philo);
	if (!table->philosopher)
		return (exit_error("malloc failed"));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philo);
	if (!table->forks)
		return (exit_error("malloc failed"));
	table->is_dead = false;
	i = 0;
	while (i < table->num_of_philo)
	{
		table->philosopher[i].philo_id = i + 1;
		table->philosopher[i].eat_counter = 0;
		table->philosopher[i].left_fork = &table->forks[i];
		table->philosopher[i].right_fork = &table->forks[(i + 1)
			% table->num_of_philo];
		table->philosopher[i].table = table;
		i++;
	}
	return (init_mutex(table));
}
