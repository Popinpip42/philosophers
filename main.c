#include "philosophers.h"

void  print_int_arr(int *arr, int len)
{
  int n = 0;
  while (n < len)
  {
    printf("item [%d] - %d\n", n+1, arr[n]);
    n++;
  }
}

void  print_usage_msg()
{
  printf("==== Usage : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
  printf("==== Example : \"5 1 2 3 4\" \"4 3 2 1 \" \n");
  printf("==== (Only Positve numbers allowed) ");
}

int	main(int argc, char **argv)
{
  /* TODO: Ideally: (Time to eat = Time to sleep +  Time to think)
   * - (Time to eat - Time to sleep = Time to think)
   *   if (Time to sleep > Time to eat)
   *      - While (thinking)
   *          - time_lost++; (Time lost must be less than Time_to_die)
   * - (Time to eat > Time to die)
   */

  t_table *table;
  t_node  *head;
  int     *valid_args;
  int     valid_args_len;
  //pthread *pthread; //TODO: Create pthread array

  valid_args = validate_argv(argc, argv, &is_valid_pos_int, &valid_args_len);
  if (!valid_args)
    return (-1);
  printf("Valid_args_len %d\n", valid_args_len);
  //TODO: Create a function that check, that n_philos > 0, and other cases ...
  if (valid_args_len < 4 || valid_args_len > 5)
    return (print_usage_msg(), -1);
  //print_int_arr(valid_args, valid_args_len);

  table = init_table(valid_args[0]);
  if (!table)
    return (free(valid_args), -1);

  head = create_table(table->n_philos, valid_args, valid_args_len, table);
  if (head)
  {
    printf("Correctly initialized\n");
    print_table(head);
  }
  else {
    printf("Not correctly initialized\n");
    free(valid_args);
    clear_table(&table);
    return (-1);
  }
	
  //TODO:
  /*
  if (valid_args_len == 4) //(head->times_to_eat == -1)
  {
    //Run_simulation_infinetly;
    //Pthread_detach;
  }
  else
  {
    //Run_simulation(times_to_eat);
    //Pthread_join;
  }
  */

  clear_list(&head);
  if (head == NULL)
    printf("======== CLEANED UP\n");
  else {
    printf("==== head %p\n", head);
    print_node(head);
  }
  free(valid_args);
  clear_table(&table);
  if (table == NULL)
    printf("======== CLEANED UP TABLE\n");
  else
    printf("======== ERROR CLEANING TABLE\n");
  return (0);
}

//TODO:
// SANITIZE
// cc -fsanitize=address -g main.c init_table.c create_table.c split_on.c validate_argv.c validation_func.c strings.c simulation.c
// DEBUG
// cc -g main.c init_table.c create_table.c split_on.c validate_argv.c validation_func.c strings.c simulation.c
// LEAKS:
// leaks -atExit -- ./a.out 10 1 2 3 4 5


/* logs format
 * ◦ timestamp_in_ms X has taken a fork
 * ◦ timestamp_in_ms X is eating
 * ◦ timestamp_in_ms X is sleeping
 * ◦ timestamp_in_ms X is thinking
 * ◦ timestamp_in_ms X died
 */

/* OTHER
 * - logs can not be altered/broken 
 *   by other philos log
 * - No more than 10ms between 
 *   the dead of a philo and the log
 */

/* PHILOS PLACING
 * - philo with id (1) sits next to philo(N)
 * - others sit between N-1 and N+1
 * - EX :
 * - N-1-2-3-4-N
 */

/* GENERAL INSTRUCTIONS
 *
 * - one or N philos sit
 * - one bowl of spaghetti in the middle
 * - philos can ( EAT - THINK - SLEEP )
 * - 	"CAN ONLY DO ONE AT A GIVEN TIME" 
 * - there is N fork 
 * - two forks(left/rigth) required w EATING
 * -    (EAT -> SLEEP -> THINK)
 * - if a philo dies of starvation -> EXIT
 * - "philos should never die of starvation"
 * - "philos dont talk to each other"
 * - "philos dont know if other philo will die"
 */

