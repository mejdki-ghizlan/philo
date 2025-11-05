/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:08:56 by ael-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 01:11:46 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_print(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->table->print_mutex);
    if (philo->table->is_dead == false)
        printf("%ld %d %s\n", get_time() - philo->start_time, philo->philo_id, msg);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

void sleeping(t_philo *philo)
{
    ft_print(philo, "is sleeping");
    ft_sleep(philo->table->time_to_sleep);
}

void single_philo_die(t_table *table, t_philo *philo)
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

void eating(t_table *table, t_philo *philo)
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

void philo_loop(t_philo *philo)
{
    t_table *table = philo->table;

    if (philo->philo_id % 2 != 0)
        ft_sleep(1);
    while (1)
    {
        pthread_mutex_lock(&table->checker_death);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->checker_death);
            break;
        }
        pthread_mutex_unlock(&table->checker_death);
        ft_print(philo, "is thinking");
        eating(table, philo);
        sleeping(philo);
    }
}

void *routine(void *param)
{
    t_philo *philo = (t_philo *)param;
    t_table *table = philo->table;

    if (table->num_of_philo == 1)
    {
        single_philo_die(table, philo); // Handles single philosopher case
        return (NULL);
    }
    philo_loop(philo);
    return (NULL);
}


int start_routine(t_table *table)
{
    int i;
    long start_time;

    i = 0;
    start_time = get_time();
    while (i < table->num_of_philo)
    {
        table->philosopher[i].start_time = start_time;// why here
        table->philosopher[i].last_meal = start_time;// why here
        if (pthread_create(&table->philosopher[i].thread, NULL, &routine, &table->philosopher[i]))
            return (exit_error("thread create failed"));
        i++;
    }
    monitor(table);
    i = 0;
    while (i < table->num_of_philo)
        pthread_join(table->philosopher[i++].thread, NULL);
    return (0);
}

long get_time()
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return (1); // Error handling can be improved as needed
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
