/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:30:34 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:40:51 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->is_dead == false)
		printf("%ld %d %s\n", get_time() - philo->start_time, philo->philo_id,
			msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_sleep(philo->table->time_to_sleep);
}
