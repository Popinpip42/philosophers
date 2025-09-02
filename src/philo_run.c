#include "../include/philosophers.h"

int	get_state(t_table *table)
{
	int	i_ret;

	pthread_mutex_lock(&table->state_mutex);
	i_ret = table->simulation_state;
	pthread_mutex_unlock(&table->state_mutex);
	return (i_ret);
}

void	add_death(t_table *table)
{
	pthread_mutex_lock(&table->deaths_mutex);
	table->deaths_count++;
	pthread_mutex_unlock(&table->deaths_mutex);
}

void	ft_sleep(t_table *table, long time_to_sleep)
{
	long	wake_up;

	wake_up = get_time_ms() + time_to_sleep;
	while (get_time_ms() < wake_up)
	{
		if (!get_state(table))
			break ;
		usleep(100);
	}
}

void	*one_philo_run(t_node philo_data, t_table *table)
{
	pthread_mutex_lock(&philo_data->fork_mutex);
	//TODO: change get_time_ms().. It must be called from print_trace()
	// get_time_ms - (table->start_time)
	print_trace(table, philo_data->id, get_time_ms(), "has taken fork");
	ft_sleep(table, philo_data->time_to_die);
	add_death(table);
	print_trace(table, philo_data->id, get_time_ms(), " DIED\n");
	pthread_mutex_unlock(&philo_data->fork_mutex);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_node		*philo_data;
	t_table		*table;
	long		elapsed_time;

	philo_data = (t_node *)arg;
	table = philo_data->table;
	philo_data->last_meal_time = table->start_time;
	start_delay(table->start_time);

	if (table->n_philos == 1)
		return (one_philo_run(philo_data));
	{
		print_trace(table, philo_data->id, get_time_ms(), " ONLY ONE PHILO");
		philo_data->is_alive = 0;
		pthread_mutex_lock(&table->deaths_mutex);
		table->deaths_count++;
		printf("<------ Completed_count : %d, Deaths_count : %d ----->\n", table->completed_count, table->deaths_count);
		pthread_mutex_unlock(&table->deaths_mutex);
		break;
	}


	while (philo_data->is_alive)
	{
		if (!table || !get_state(table))
			break;
		elapsed_time = get_time_ms() - philo_data->last_meal_time;
		if (elapsed_time > (long)philo_data->time_to_die && get_state(table))
		{
			print_trace(table, philo_data->id, get_time_ms(), " DIED\n");
			add_death(table);
			printf("<------ Completed_count : %d, Deaths_count : %d ----->\n", table->completed_count, table->deaths_count);
			//print_eating_times(table, philo_data->id, get_time_ms(), philo_data->times_to_eat);
			//print_death_reason(table, philo_data->id, get_time_ms(), philo_data->times_to_eat);
			philo_data->is_alive = 0;
			break;
		}
		// Odd/even strategy for taking forks
		if (philo_data->id % 2 == 0)
		{
			// Even ID: Pick up left fork first, then right fork
			if (get_state(table))
			{
				pthread_mutex_lock(&philo_data->fork_mutex);
			}
			if (get_state(table))
			{
				pthread_mutex_lock(&philo_data->next->fork_mutex);
				print_trace(table, philo_data->id, get_time_ms(), "has taken left fork");
				print_trace(table, philo_data->id, get_time_ms(), "has taken right fork");
			}
			else
			{
				pthread_mutex_unlock(&philo_data->fork_mutex);
				pthread_mutex_unlock(&philo_data->next->fork_mutex);
			}
		}
		else
		{
			// Odd ID: Pick up right fork first, then left fork
			if (get_state(table))
			{
				pthread_mutex_lock(&philo_data->next->fork_mutex);
			}
			if (get_state(table))
			{
				pthread_mutex_lock(&philo_data->fork_mutex);
				print_trace(table, philo_data->id, get_time_ms(), "has taken right fork");
				print_trace(table, philo_data->id, get_time_ms(), "has taken left fork");
			}
			else
			{
				pthread_mutex_unlock(&philo_data->fork_mutex);
				pthread_mutex_unlock(&philo_data->next->fork_mutex);
			}
		}

		// Eating
		if (get_state(table))
		{
			philo_data->last_meal_time = get_time_ms();
			print_trace(table, philo_data->id, philo_data->last_meal_time, "is eating");
			usleep(philo_data->time_to_eat * 1000);
		}

		// Release forks
		pthread_mutex_unlock(&philo_data->fork_mutex);
		pthread_mutex_unlock(&philo_data->next->fork_mutex);

		if (philo_data->times_to_eat != -1)
			philo_data->times_to_eat--;

		//print_eating_times(table, philo_data->id, get_time_ms(), philo_data->times_to_eat);

		if (philo_data->times_to_eat == 0 && get_state(table))
		{
			pthread_mutex_lock(&table->completed_mutex);
			table->completed_count++;
			printf("<------ Completed_count : %d, Deaths_count : %d ----->\n", table->completed_count, table->deaths_count);
			pthread_mutex_unlock(&table->completed_mutex);
			break;
		}

		// Sleeping
		if (get_state(table))
		{
			print_trace(table, philo_data->id, get_time_ms(), "is sleeping");
			usleep(philo_data->time_to_sleep * 1000);
		}

		// Thinking
		if (get_state(table))
		{
			print_trace(table, philo_data->id, get_time_ms(), "is thinking");
			//usleep(5 * 1000);
			usleep(9660);
		}
	}
	return (NULL);
}

