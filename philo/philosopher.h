/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:10:29 by ael-mejd          #+#    #+#             */
/*   Updated: 2025/11/04 04:21:14 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
    int philo_id;
    long last_meal;
    int eat_counter;
    long start_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_table *table;
} t_philo;

typedef struct s_table
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int n_times_must_eat;
    bool is_dead;
    pthread_mutex_t checker_death;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t time_mutex;
    pthread_mutex_t dead_mutex;

    t_philo *philosopher;
} t_table;

// utils.c
long ft_atol(char *str);
int exit_error(char *str);
long get_time();

// parsing.c
int is_valid_arg(char *str);
int get_args(char **av, t_table *table);

// init.c
int init_data(t_table *table); // hado lli reja3tem men void l int 3la 7sab exit forbiden fa khesni n returner 1 ida failat bax mlli n3ayetla
// nchekcker wax kadsawer 1 bax nreturner error o nkhrej ida kan 0 kankmel

// routine.h
void *routine(void *param);
int start_routine(t_table *table);
void eating(t_table *table, t_philo *philo);
void sleeping(t_philo *philo);

void ft_print(t_philo *philo, char *msg);
void monitor(t_table *table);

void ft_sleep(int ms);
void destroy_mutexes(t_table *table);
void free_all(t_table *table);

#endif