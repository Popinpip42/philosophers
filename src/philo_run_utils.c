/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:39:50 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:39:51 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	add_death(t_table *table)
{
	pthread_mutex_lock(&table->deaths_mutex);
	table->deaths_count++;
	pthread_mutex_unlock(&table->deaths_mutex);
}

void	add_completed_count(t_table *table)
{
	pthread_mutex_lock(&table->completed_mutex);
	table->completed_count++;
	pthread_mutex_unlock(&table->completed_mutex);
}

void	*one_philo_run(t_node *philo_data, t_table *table)
{
	pthread_mutex_lock(&philo_data->fork_mutex);
	print_trace(table, philo_data->id, get_time_ms(), "has taken fork");
	ft_sleep(table, philo_data->time_to_die);
	print_trace(table, philo_data->id, get_time_ms(), " DIED\n");
	add_death(table);
	pthread_mutex_unlock(&philo_data->fork_mutex);
	return (NULL);
}
