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
	printf("<------ Completed_count : %d, Deaths_count : %d ----->\n",
		table->completed_count, table->deaths_count);
	pthread_mutex_unlock(&table->completed_mutex);
}

int	check_death(t_node *philo, t_table *table)
{
	long	elapsed;

	elapsed = get_time_ms() - philo->last_meal_time;
	if (elapsed > philo->time_to_die)
	{
		print_trace(table, philo->id, get_time_ms(), " DIED\n");
		add_death(table);
		printf("<------ Completed_count : %d, Deaths_count : %d ----->\n",
			table->completed_count, table->deaths_count);
		return (1);
	}
	return (0);
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
