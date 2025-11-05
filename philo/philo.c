/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-mejd <gel-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:28:21 by gel-mejd          #+#    #+#             */
/*   Updated: 2025/11/05 02:28:25 by gel-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac == 5 || ac == 6)
	{
		table = malloc(sizeof(t_table));
		if (!table)
			return (exit_error("malloc failed"));
		if (get_args(av, table))
		{
			free(table);
			return (exit_error("Invalid arguments"));
		}
		if (init_data(table))
		{
			free_all(table);
			return (exit_error("Initialization failed"));
		}
		start_routine(table);
		destroy_mutexes(table);
		free_all(table);
	}
	else
		return (exit_error("Invalid number of arguments"));
}
