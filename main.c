/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:20:09 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/07/21 16:20:09 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_dining(t_table *table);
static bool	start_dining(t_table *table);

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (is_valid_args(argc, argv) == false)
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	if (start_dining(table) == false)
		return (EXIT_FAILURE);
	end_dining(table);
	return (EXIT_SUCCESS);
}

static void	end_dining(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i]->thread_philo, NULL);
		i++;
	}
	if (table->nbr_philo > 1)
		pthread_join(table->thread_table, NULL);
	free_table(table);
}

static bool	start_dining(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&table->philo[i]->thread_philo, NULL,
				&dining_routines, table->philo[i]) != 0)
			return (error_msg_null(ERR_THREAD, table));
		i++;
	}
	if (table->nbr_philo > 1)
	{
		if (pthread_create(&table->thread_table, NULL, &finish_routines_reached,
				table) != 0)
			return (error_msg_null(ERR_THREAD, table));
	}
	return (true);
}
