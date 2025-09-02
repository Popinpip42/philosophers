/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:01:48 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 19:01:50 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	set_fork_order(t_node *philo, pthread_mutex_t **first,
						pthread_mutex_t **second)
{
	if (&philo->fork_mutex < &philo->next->fork_mutex)
	{
		*first = &philo->fork_mutex;
		*second = &philo->next->fork_mutex;
	}
	else
	{
		*first = &philo->next->fork_mutex;
		*second = &philo->fork_mutex;
	}
}

void	drop_forks(t_node *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	set_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

int	philo_take_forks(t_node *philo, t_table *table)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	set_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	if (!get_state(table))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	if (!get_state(table))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_trace(table, philo->id, get_time_ms(), "has taken fork");
	print_trace(table, philo->id, get_time_ms(), "has taken fork");
	return (0);
}
