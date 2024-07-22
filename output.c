/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:21:57 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/07/21 16:21:57 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*parse_status(t_state status)
{
	if (status == S_EATING)
		return ("is eating");
	else if (status == S_LEFT_FORK || status == S_RIGHT_FORK)
		return ("has taken a fork");
	else if (status == S_SLEEPING)
		return ("is sleeping");
	else if (status == S_THINKING)
		return ("is thinking");
	else if (status == S_DEAD)
		return ("died");
	else
		return ("");
}

void	log_status(t_philo *philo, t_state status)
{
	if (has_dinner_finish(philo->table) == true)
		return ;
	pthread_mutex_lock(&philo->table->log_lock);
	printf("%i %ld %s\n", get_time_ms(philo->table->start_dining),
		philo->id + 1, parse_status(status));
	pthread_mutex_unlock(&philo->table->log_lock);
}
