/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:39:57 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/03 01:53:05 by anruiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_trace(t_table *table, int id, long time, char *msg)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%lu %d %s\n", time - table->start_time, id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}

static int	check_philo_death(t_table *table, t_node *head)
{
	t_node	*ph;
	int		i;
	long	elapsed;

	ph = head;
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_lock(&table->times_to_eat_mutex);
		elapsed = get_time_ms() - ph->last_meal_time;
		pthread_mutex_unlock(&table->times_to_eat_mutex);
		if (elapsed > ph->time_to_die)
		{
			pthread_mutex_lock(&table->state_mutex);
			table->simulation_state = 0;
			pthread_mutex_unlock(&table->state_mutex);
			print_trace(table, ph->id, get_time_ms(), " DIED\n");
			return (1);
		}
		ph = ph->next;
		i++;
	}
	return (0);
}

static void	monitor_infinite(t_table *table, t_node *head)
{
	while (get_state(table))
	{
		if (check_philo_death(table, head))
			return ;
		usleep(500);
	}
}

static void	monitor_finite(t_table *table, t_node *head)
{
	while (get_state(table))
	{
		if (get_completed(table) == table->n_philos)
		{
			pthread_mutex_lock(&table->state_mutex);
			table->simulation_state = 0;
			pthread_mutex_unlock(&table->state_mutex);
			return ;
		}
		if (check_philo_death(table, head))
			return ;
		usleep(500);
	}
}

void	run_simulation(t_node *head, t_table *table)
{
	pthread_t	*philos_arr;
	long		times_to_eat;

	philos_arr = malloc(sizeof(pthread_t) * table->n_philos);
	if (!philos_arr)
		return ;
	table->start_time = get_time_ms() + (table->n_philos * 2 * 10);
	create_threads(philos_arr, head, table);
	start_delay(table->start_time);
	times_to_eat = get_times_to_eat(head, table);
	if (times_to_eat == -1)
		monitor_infinite(table, head);
	else
		monitor_finite(table, head);
	join_threads(philos_arr, table->n_philos);
	free(philos_arr);
}
