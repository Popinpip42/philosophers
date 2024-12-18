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

  //ROUTINE : take forks, eat, release forks, sleep, think ->
  while (philo_data->is_alive)
  {
    // Check if philosopher has died
    elapsed_time = get_time_ms() - philo_data->last_meal_time;
    if (elapsed_time > (long)philo_data->time_to_die)
    {
      print_trace(table, philo_data->id, get_time_ms(), "died");
      pthread_mutex_lock(&table->deaths_mutex);
      table->deaths_count++;
      pthread_mutex_unlock(&table->deaths_mutex);
      philo_data->is_alive = 0;
      break;
    }


    // Odd/even strategy for taking forks
    if (philo_data->id % 2 == 0)
    {
      // Even ID: Pick up left fork first, then right fork
      pthread_mutex_lock(&philo_data->fork_mutex);
      print_trace(table, philo_data->id, get_time_ms(), "has taken a fork");
      pthread_mutex_lock(&philo_data->next->fork_mutex);
      print_trace(table, philo_data->id, get_time_ms(), "has taken a fork");
    }
    else
    {
      // Odd ID: Pick up right fork first, then left fork
      pthread_mutex_lock(&philo_data->next->fork_mutex);
      print_trace(table, philo_data->id, get_time_ms(), "has taken a fork");
      pthread_mutex_lock(&philo_data->fork_mutex);
      print_trace(table, philo_data->id, get_time_ms(), "has taken a fork");
    }

    // Eating
    print_trace(table, philo_data->id, get_time_ms(), "is eating");
    usleep(philo_data->time_to_eat * 1000);
    philo_data->last_meal_time = get_time_ms();

    // Release forks
    pthread_mutex_unlock(&philo_data->fork_mutex);
    pthread_mutex_unlock(&philo_data->next->fork_mutex);

    if (philo_data->times_to_eat != -1)
      philo_data->times_to_eat--;

    if (philo_data->times_to_eat == 0)
    {
      pthread_mutex_lock(&table->completed_mutex);
      table->completed_count++;
      pthread_mutex_unlock(&table->completed_mutex);
      break;
    }

    // Sleeping
    print_trace(table, philo_data->id, get_time_ms(), "is sleeping");
    usleep(philo_data->time_to_sleep * 1000);

    // Thinking
    print_trace(table, philo_data->id, get_time_ms(), "is thinking");
    usleep(1000); // Simulate thinking
  }
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
