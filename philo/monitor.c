/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:28:42 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:28:45 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_philo_dead(t_table *table, t_philo *philo)
{
	long	tmp;

	pthread_mutex_lock(&table->time_mutex);
	tmp = get_time() - philo->last_meal;
	pthread_mutex_unlock(&table->time_mutex);
	if (tmp > table->time_to_die)
	{
		pthread_mutex_lock(&table->print_mutex);
		pthread_mutex_lock(&table->checker_death);
		if (!table->is_dead)
		{
			table->is_dead = true;
			printf("%ld %d died\n", get_time() - philo->start_time,
				philo->philo_id);
		}
		pthread_mutex_unlock(&table->checker_death);
		pthread_mutex_unlock(&table->print_mutex);
		return (1);
	}
	return (0);
}

void	monitor(t_table *table)
{
	int	i;
	int	checker;

	while (!table->is_dead)
	{
		i = 0;
		checker = 0;
		while (i < table->num_of_philo)
		{
			if (check_philo_dead(table, &table->philosopher[i]))
				return ;
			if (table->n_times_must_eat != -1
				&& table->philosopher[i].eat_counter >= table->n_times_must_eat)
				checker++;
			i++;
		}
		if (checker == table->num_of_philo)
		{
			pthread_mutex_lock(&table->checker_death);
			table->is_dead = true;
			pthread_mutex_unlock(&table->checker_death);
			return ;
		}
		ft_sleep(1);
	}
}
