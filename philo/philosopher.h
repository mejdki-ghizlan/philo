/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:42:50 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:42:53 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <memory.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					philo_id;
	long				last_meal;
	int					eat_counter;
	long				start_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_times_must_eat;
	bool				is_dead;
	pthread_mutex_t		checker_death;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		dead_mutex;

	t_philo				*philosopher;
}						t_table;

// init.c
int						init_mutex(t_table *table);
int						init_data(t_table *table);

// monitor.c
int						check_philo_dead(t_table *table, t_philo *philo);
void					monitor(t_table *table);

// parsing.c
int						is_valid_arg(char *str);
int						get_args(char **av, t_table *table);

// routine.h
void					single_philo_die(t_table *table, t_philo *philo);
void					eating(t_table *table, t_philo *philo);
void					philo_loop(t_philo *philo);
void					*routine(void *param);
int						start_routine(t_table *table);

// utils.c
long					ft_atol(char *str);
int						exit_error(char *str);
void					ft_sleep(int ms);
void					destroy_mutexes(t_table *table);
void					free_all(t_table *table);

// utils2.c
void					ft_print(t_philo *philo, char *msg);
long					get_time(void);
void					sleeping(t_philo *philo);

#endif