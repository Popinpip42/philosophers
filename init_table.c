#include "philosophers.h"

t_table *init_table(int n_philos)
{
  t_table *new_table;

  new_table = (t_table *)malloc(sizeof(t_table));
  if (!new_table)
    return (NULL);
  //TODO: Validate args
  new_table->shared_bowl = 0;
  new_table->n_philos = n_philos;
  //TODO: Assuming argv[1] only contains a valid numbers
  //And is below 200 or 250
  if (pthread_mutex_init(&new_table->bowl_mutex, NULL) != 0)
    return (NULL);
  return (new_table);
}


void    clear_table(t_table **table)
{
  pthread_mutex_destroy(&(*table)->bowl_mutex);
  free(*table);
  *table = NULL;
}
