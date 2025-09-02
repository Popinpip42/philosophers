#include "../include/philosophers.h"

static void	create_threads(pthread_t *philos_arr, t_node *head, t_table *table)
{
	int			m;
	t_node		*tmp;

	m = 0;
	tmp = head;
	while (m < table->n_philos)
	{
		//printf("INIT thread with id %d\n", tmp->id);
		pthread_create(&philos_arr[m], NULL, &philosopher_routine, (void *)tmp);
		tmp = tmp->next;
		m++;
	}
}

static void	join_threads(pthread_t *philos_arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philos_arr[i], NULL);
		i++;
	}
}

static void	monitor_infinite(t_table *table)
{
	while (1)
	{
		if (get_deaths(table) > 0)
		{
			pthread_mutex_lock(&table->state_mutex);
			table->simulation_state = 0;
			pthread_mutex_unlock(&table->state_mutex);
			break ;
		}
		usleep(1000);
	}
}

static void	monitor_finite(t_table *table)
{
	while (1)
	{
		if (get_completed(table) == table->n_philos
			|| get_deaths(table) == table->n_philos)
		{
			pthread_mutex_lock(&table->state_mutex);
			table->simulation_state = 0;
			pthread_mutex_unlock(&table->state_mutex);
			break ;
		}
		usleep(1000);
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
	times_to_eat = head->times_to_eat;
	if (times_to_eat == -1)
		monitor_infinite(table);
	else
		monitor_finite(table);
	print_trace(table, -1, get_time_ms(), "================= END =================\n");
	join_threads(philos_arr, table->n_philos);
	free(philos_arr);
	printf("================= REAL END =================\n");
}
