#include "../include/philosophers.h"

static void	philo_take_forks(t_node *philo, t_table *table)
{
	pthread_mutex_lock(&philo->fork_mutex);
	print_trace(table, philo->id, get_time_ms(), "has taken left fork");
	pthread_mutex_lock(&philo->next->fork_mutex);
	print_trace(table, philo->id, get_time_ms(), "has taken right fork");
}

static int	philo_eat(t_node *philo, t_table *table)
{
	philo->last_meal_time = get_time_ms();
	print_trace(table, philo->id, philo->last_meal_time, "is eating");
	ft_sleep(table, philo->time_to_eat);
	if (get_state(table) && philo->times_to_eat != -1)
	{
		philo->times_to_eat--;
		//printf("<------ ID: %d times_to_eat : %d, Deaths_count : %d ----->\n",
		//	philo->id, philo->times_to_eat, table->deaths_count);
		if (philo->times_to_eat == 0)
		{
			add_completed_count(table);
			pthread_mutex_unlock(&philo->fork_mutex);
			pthread_mutex_unlock(&philo->next->fork_mutex);
			return (1);
		}
	}
	return (0);
}

static void	philo_sleep(t_node *philo, t_table *table)
{
	print_trace(table, philo->id, get_time_ms(), "is sleeping");
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->next->fork_mutex);
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
	else if (philo->id % 2 != 0)
		philo_think(philo, table, 1);
	while (get_state(table))
	{
		if (check_death(philo, table))
			break ;
		philo_take_forks(philo, table);
		if (philo_eat(philo, table))
			break ;
		philo_sleep(philo, table);
		philo_think(philo, table, 0);
	}
	return (NULL);
}
