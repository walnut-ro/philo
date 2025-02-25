/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_finish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:32:48 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/07/21 16:32:48 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dinner_finished_reached(t_table *table);

void	*finish_routines_reached(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->time_must_eat == 0)
		return (NULL);
	set_dinner_end_prop(table, false);
	while (true)
	{
		if (dinner_finished_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static bool	kill_philo(t_philo *philo)
{
	if (!philo)
        return (false);
	if ((datetime_now() - philo->last_meal) >= philo->table->time_to_die)
	{
		log_status(philo, S_DEAD);
		set_dinner_end_prop(philo->table, true);
		pthread_mutex_unlock(&philo->general_meal_lock);
		return (true);
	}
	return (false);
}

static bool	dinner_finished_reached(t_table *table)
{
	int		i;
	bool	eat_enough;

	i = 0;
	eat_enough = true;
	while (i < table->nbr_philo)
	{
		pthread_mutex_lock(&table->philo[i]->general_meal_lock);
		if (kill_philo(table->philo[i]) == true)
			return (true);
		if (table->time_must_eat != -1)
			if (table->philo[i]->nbr_meals_done < table->time_must_eat)
				eat_enough = false;
		pthread_mutex_unlock(&table->philo[i]->general_meal_lock);
		i++;
	}
	if (table->time_must_eat != -1 && eat_enough == true)
	{
		set_dinner_end_prop(table, true);
		return (true);
	}
	return (false);
}
