/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:33:15 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/07/21 16:33:15 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	datetime_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_time_ms(int start_dining)
{
	return (datetime_now() - start_dining);
}

void	thread_sleep(t_table *table, time_t duration)
{
	time_t	time_wake_up;

	time_wake_up = datetime_now() + duration;
	while (datetime_now() < time_wake_up)
	{
		if (has_dinner_finish(table))
			break ;
		usleep(100);
	}
}

long	handle_thinking_time(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->general_meal_lock);
	time_to_think = (philo->table->time_to_die - (datetime_now()
				- philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->general_meal_lock);
	if (time_to_think > 500)
		return (200);
	else
		return (1);
}
