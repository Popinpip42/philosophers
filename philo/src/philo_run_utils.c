/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:39:50 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/03 01:42:10 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
	print_trace(table, philo_data->id, get_time_ms(), "died\n");
	pthread_mutex_unlock(&philo_data->fork_mutex);
	return (NULL);
}
