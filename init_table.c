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

  return (new_table);
}
