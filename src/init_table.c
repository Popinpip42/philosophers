/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:39:29 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:39:30 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_table	*init_table(int n_philos)
{
	t_table	*new_table;

	new_table = (t_table *)malloc(sizeof(t_table));
	if (!new_table)
		return (NULL);
	new_table->n_philos = n_philos;
	new_table->deaths_count = 0;
	new_table->completed_count = 0;
	new_table->simulation_state = 1;
	if (pthread_mutex_init(&new_table->state_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&new_table->print_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&new_table->deaths_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&new_table->completed_mutex, NULL) != 0)
		return (NULL);
	return (new_table);
}

void	clear_table(t_table **table)
{
	pthread_mutex_destroy(&(*table)->state_mutex);
	pthread_mutex_destroy(&(*table)->print_mutex);
	pthread_mutex_destroy(&(*table)->deaths_mutex);
	pthread_mutex_destroy(&(*table)->completed_mutex);
	free(*table);
	*table = NULL;
}
