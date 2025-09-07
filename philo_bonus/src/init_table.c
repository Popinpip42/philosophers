#include "../include/philo_bonus.h"

t_table	*init_table(int n_philos)
{
	t_table	*new_table;

	new_table = (t_table *)malloc(sizeof(t_table));
	if (!new_table)
		return (NULL);
	new_table->n_philos = n_philos;
	new_table->completed_count = 0;
	new_table->simulation_state = 1;
	return (new_table);
}

void	clear_table(t_table **table)
{
	free(*table);
	*table = NULL;
}
