/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:17:19 by dlevinsc          #+#    #+#             */
/*   Updated: 2024/07/20 15:17:19 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define ERR_PARAM "Wrong arguments. Check the subject and try again.\n"
# define ERR_THREAD	"Error: Could not create thread.\n"
# define ERR_MALLOC	"Error: Could not allocate memory.\n"
# define ERR_MUTEX	"Error: Could not create mutex.\n"
# define ERR_INV_INP "Invalid input in [%li].\n"
# define ERR_SIXTY "Invalid input. Must be greater than 60.\n"

# ifndef PRETTY
#  define PRETTY 1
# endif

typedef int bool;
# define true 1
# define false 0

typedef struct s_table	t_table;

typedef enum e_fork
{
	F_LEFT = 0,
	F_RIGHT = 1
}	t_fork;

typedef enum e_state
{
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DEAD,
	S_LEFT_FORK,
	S_RIGHT_FORK,
	S_END_dining
}	t_state;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	pthread_t		thread_table;
	time_t			start_dining;
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_must_eat;
	t_philo			**philo;
	bool			dinner_end;
	pthread_mutex_t	dinner_end_lock;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	log_lock;
}				t_table;

typedef struct s_philo
{
	pthread_t		thread_philo;
	long			id;
	int				fork[2];
	t_table			*table;
	long			nbr_meals_done;
	pthread_mutex_t	general_meal_lock;
	time_t			last_meal;
}				t_philo;

void	*dining_routines(void *data);
bool	is_valid_args(int argc, char **argv);
long	ft_ato_long(const char *str);
bool	ft_isdigit(int c);
t_table	*init_table(int argc, char **argv);
bool	error_msg_null(char *str, t_table *table);
int		datetime_now(void);
int		get_time_ms(int start_dining);
void	log_status(t_philo *philo, t_state status);
void	thread_sleep(t_table *table, time_t duration);
void	*free_table(t_table *table);
bool	has_dinner_finish(t_table *table);
void	*finish_routines_reached(void *data);
void	set_dinner_end_prop(t_table *table, bool value);
void	set_last_meal_prop(t_philo *philo, time_t value);
void	increment_times_eat_prop(t_philo *philo);
bool	is_param_valid(t_table *table);
long	handle_thinking_time(t_philo *philo);

#endif