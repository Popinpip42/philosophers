/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:39:44 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:39:45 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	philo_eat(t_node *philo, t_table *table)
{
	if (!get_state(table))
		return (1);
	philo->last_meal_time = get_time_ms();
	print_trace(table, philo->id, philo->last_meal_time, "is eating");
	ft_sleep(table, philo->time_to_eat);
	if (get_state(table) && philo->times_to_eat != -1)
	{
		pthread_mutex_lock(&table->times_to_eat_mutex);
		philo->times_to_eat--;
		pthread_mutex_unlock(&table->times_to_eat_mutex);
		if (get_times_to_eat(philo, table) == 0)
		{
			add_completed_count(table);
			drop_forks(philo);
			return (1);
		}
	}
	drop_forks(philo);
	return (0);
}

static void	philo_sleep(t_node *philo, t_table *table)
{
	print_trace(table, philo->id, get_time_ms(), "is sleeping");
	ft_sleep(table, philo->time_to_sleep);
}

static void	philo_think(t_node *philo, t_table *table, int silent)
{
	long	time_to_think;

	time_to_think = (philo->time_to_die
			- (get_time_ms() - philo->last_meal_time)
			- philo->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		print_trace(table, philo->id, get_time_ms(), "is thinking");
	ft_sleep(table, time_to_think);
}

static int	take_forks_eat(t_node *philo, t_table *table)
{
	if (philo_take_forks(philo, table))
		return (1);
	if (philo_eat(philo, table))
		return (1);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_node	*philo;
	t_table	*table;

	philo = (t_node *)arg;
	table = philo->table;
	philo->last_meal_time = table->start_time;
	start_delay(table->start_time);
	if (table->n_philos == 1)
		return (one_philo_run(philo, table));
	else if (philo->id % 2 == 0)
		usleep(2000);
	while (get_state(table))
	{
		if (check_death(philo, table))
			break ;
		if (take_forks_eat(philo, table))
			break ;
		if (!get_state(table))
			break ;
		philo_sleep(philo, table);
		if (!get_state(table))
			break ;
		philo_think(philo, table, 0);
	}
	return (NULL);
}
