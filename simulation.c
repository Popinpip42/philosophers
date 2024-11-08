#include "philosophers.h"

long  get_time_ms()
{
  struct timeval  tv;
  long            res;

  gettimeofday(&tv, NULL);
  res = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
  return (res);
}

void  print_trace(t_table *table, int id, long time, char *msg)
{
  pthread_mutex_lock(&table->print_mutex);
  printf("!!!!==== %lu ID: %d %s\n", time - table->start_time, id, msg);
  pthread_mutex_unlock(&table->print_mutex);
}

void add_to_queue(t_table *table, int id)
{
}

void  *philosopher_routine(void *arg)
{
  t_node    *philo_data;
  t_table   *table;
  long      elapsed_time;

  philo_data = (t_node *)arg;
  table = philo_data->table;

  //while (1)
  {
    //Check if philospher died
  }
  //take forks, eat, release forks, sleep, think ->
}

void update_state_table(t_table *table)
{
}

void  run_simulation(t_node *head, t_table *table)
{
  long      initial_time;
  pthread_t philos_arr[table->n_philos];
  int       m;
  t_node    *tmp;

  initial_time = get_time_ms();
  table->start_time = initial_time;
  printf("=== Table time start  in simulation() : %lu\n", table->start_time);

  //Start threads// Launch them
  m = 0;
  tmp = head;
  while (m < table->n_philos)
  {
    printf("INIT thread with id %d\n", tmp->id);
    tmp->last_meal_time = table->start_time; //TODO: for first iteration only
    pthread_create(&philos_arr[m], NULL, &philosopher_routine, (void *)tmp);
    pthread_detach(philos_arr[m]);
    tmp = tmp->next;
    m++;
  }

  //- Let threads add them selfs to the queue
  //Start consuming queue
  while (1)
  {
    //print_trace(table, -1, get_time_ms(), "=== from main_loop");
    if (table->deaths_count > 0 && head->times_to_eat == -1)
      break ;
    if (table->completed_count == table->n_philos && head->times_to_eat >= 0)
      break ;
    //Update values of the states_TABLE so philos can eat
    //Our queue is stored into our table struct as a int array of size table->n_philos
    //if (queue_size == p || queue_size == 1)
    //  update_state_table(table->state_table);

    //update_state_table(table);
    //usleep(1000);
  }
  printf("================= END =================\n");

  //TODO: philos update state table to -1 after eating
  // - State table is updated by the queue manager
  // - philos add them selfs to the queue
  //
}
