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

int	get_times_to_eat(t_node *philo, t_table *table)
{
	int	i_ret;

	pthread_mutex_lock(&table->times_to_eat_mutex);
	i_ret = philo->times_to_eat;
	pthread_mutex_unlock(&table->times_to_eat_mutex);
	return (i_ret);
}

void	create_threads(pthread_t *philos_arr, t_node *head, t_table *table)
{
	int			m;
	t_node		*tmp;

	m = 0;
	tmp = head;
	while (m < table->n_philos)
	{
		pthread_create(&philos_arr[m], NULL, &philosopher_routine, (void *)tmp);
		tmp = tmp->next;
		m++;
	}
}

void	join_threads(pthread_t *philos_arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philos_arr[i], NULL);
		i++;
	}
}
