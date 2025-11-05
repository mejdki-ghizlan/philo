/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:10:55 by ael-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 00:32:42 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

long ft_atol(char *str)
{
    int i;
    long res;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    res = 0;
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        res = res * 10 + (str[i] - 48);
        i++;
    }
    return (res);
}

int exit_error(char *str)
{
    printf("%s\n", str);
    return (1);
}

void ft_sleep(int ms)
{
    long start;

    start = get_time();
    while (get_time() - start < ms)
        usleep(500);
}


void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->checker_death);
	pthread_mutex_destroy(&table->time_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
}

void	free_all(t_table *table)
{
	if (!table)
		return;
	if (table->forks)
		free(table->forks);
	if (table->philosopher)
		free(table->philosopher);
	free(table);
}
