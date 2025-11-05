/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:32:34 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:42:01 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	single_philo_die(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	ft_sleep(table->time_to_die);
	ft_print(philo, "died");
	pthread_mutex_lock(&table->checker_death);
	table->is_dead = true;
	pthread_mutex_unlock(&table->checker_death);
	pthread_mutex_unlock(philo->right_fork);
}

void	eating(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&table->time_mutex);
	philo->last_meal = get_time();
	philo->eat_counter++;
	pthread_mutex_unlock(&table->time_mutex);
	ft_print(philo, "is eating");
	ft_sleep(table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_loop(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->philo_id % 2 != 0)
		ft_sleep(1);
	while (1)
	{
		pthread_mutex_lock(&table->checker_death);
		if (table->is_dead)
		{
			pthread_mutex_unlock(&table->checker_death);
			break ;
		}
		pthread_mutex_unlock(&table->checker_death);
		ft_print(philo, "is thinking");
		eating(table, philo);
		sleeping(philo);
	}
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)param;
	table = philo->table;
	if (table->num_of_philo == 1)
	{
		single_philo_die(table, philo);
		return (NULL);
	}
	philo_loop(philo);
	return (NULL);
}

int	start_routine(t_table *table)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = get_time();
	while (i < table->num_of_philo)
	{
		table->philosopher[i].start_time = start_time;
		table->philosopher[i].last_meal = start_time;
		if (pthread_create(&table->philosopher[i].thread, NULL, &routine,
				&table->philosopher[i]))
			return (exit_error("thread create failed"));
		i++;
	}
	monitor(table);
	i = 0;
	while (i < table->num_of_philo)
		pthread_join(table->philosopher[i++].thread, NULL);
	return (0);
}
