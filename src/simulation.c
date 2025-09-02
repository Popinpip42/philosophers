#include "../include/philosophers.h"

//==================================== AUXILIAR FUNCS
void  print_eating_times(t_table *table, int id, long time, int times)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("!!!!!!!!!!!-----> %lu ID: %d has eaten %d times,\n", time - table->start_time, id, times);
	printf("<------ Completed_count : %d, Deaths_count : %d ----->\n", table->completed_count, table->deaths_count);
	pthread_mutex_unlock(&table->print_mutex);
}

void  print_death_reason(t_table *table, int id, long time, int times_to_eat)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("<-----DEATH REASON -----> %lu ID: %d, Deaths Counter %d, Times to Eat %d\n", time - table->start_time, id, table->deaths_count, times_to_eat);
	pthread_mutex_unlock(&table->print_mutex);
}
//====================================

//TODO: why would we use time_t instead of long?
void	run_simulation(t_node *head, t_table *table)
{
	pthread_t	philos_arr[table->n_philos]; //TODO: malloc this
	//pthread_t	*philos_arr; //TODO: malloc this
	int			m;
	t_node		*tmp;

	//TODO: sync start time for monitor and philos threads
	table->start_time = get_time_ms() + (table->n_philos * 2 * 10);
	//printf("=== Table time start  in simulation() : %lu\n", table->start_time);

	m = 0;
	tmp = head;
	while (m < table->n_philos)
	{
		//printf("INIT thread with id %d\n", tmp->id);
		pthread_create(&philos_arr[m], NULL, &philosopher_routine, (void *)tmp);
		tmp = tmp->next;
		m++;
	}


	while (1)
	{
		//print_trace(table, -1, get_time_ms(), "=== from main_loop");
		if (table->deaths_count > 0 && head->times_to_eat == -1)
		{
			table->simulation_state = 0;
			//print_trace(table, -1, get_time_ms(), "finish due to times to eat -1 and one philo died");
			break ;
		}
		if ((table->completed_count == table->n_philos && head->times_to_eat >= 0)
			|| (table->deaths_count == table->n_philos && head->times_to_eat >= 0))
		{
			table->simulation_state = 0;
			//print_trace(table, -1, get_time_ms(), "finish due to all died before full eating or they full");
			break ;
		}
	}
	print_trace(table, -1, get_time_ms(), "================= END =================\n");
	m = 0;
	while (m < table->n_philos)
		pthread_join(philos_arr[m++], NULL);
	printf("================= REAL END =================\n");
}
