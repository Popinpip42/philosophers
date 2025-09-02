/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:11 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:40:13 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_trace(t_table *table, int id, long time, char *msg)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%lu ID: %d %s\n", time - table->start_time, id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}

int	get_state(t_table *table)
{
	int	i_ret;

	pthread_mutex_lock(&table->state_mutex);
	i_ret = table->simulation_state;
	pthread_mutex_unlock(&table->state_mutex);
	return (i_ret);
}

int	get_completed(t_table *table)
{
	int	i_ret;

	pthread_mutex_lock(&table->completed_mutex);
	i_ret = table->completed_count;
	pthread_mutex_unlock(&table->completed_mutex);
	return (i_ret);
}

int	get_deaths(t_table *table)
{
	int	i_ret;

	pthread_mutex_lock(&table->deaths_mutex);
	i_ret = table->deaths_count;
	pthread_mutex_unlock(&table->deaths_mutex);
	return (i_ret);
}
