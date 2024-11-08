#include "philosophers.h"

t_table *init_table(int n_philos)
{
  t_table *new_table;

  new_table = (t_table *)malloc(sizeof(t_table));
  if (!new_table)
    return (NULL);
  new_table->n_philos = n_philos;
  new_table->state_table = (int *)malloc(n_philos * sizeof(int));
  if (!new_table->state_table)
    return (NULL);
  int i = 0;
  while (i < new_table->n_philos)
    new_table->state_table[i++] = -1;
  new_table->queue = (int *)malloc(n_philos * sizeof(int));
  if (!new_table->queue)
    return (NULL);
  new_table->queue_size = 0;
  new_table->deaths_count = 0;
  new_table->completed_count = 0;
  if (pthread_mutex_init(&new_table->queue_mutex, NULL) != 0)
    return (NULL);
  if (pthread_mutex_init(&new_table->queue_mutex2, NULL) != 0)
    return (NULL);
  if (pthread_mutex_init(&new_table->deaths_mutex, NULL) != 0)
    return (NULL);
  if (pthread_mutex_init(&new_table->completed_mutex, NULL) != 0)
    return (NULL);
  return (new_table);
}

void    clear_table(t_table **table)
{
  pthread_mutex_destroy(&(*table)->deaths_mutex);
  pthread_mutex_destroy(&(*table)->completed_mutex);
  pthread_mutex_destroy(&(*table)->queue_mutex);
  pthread_mutex_destroy(&(*table)->queue_mutex2);
  if ((*table)->state_table)
    free((*table)->state_table);
  if ((*table)->queue)
    free((*table)->queue);
  free(*table);
  *table = NULL;
}
