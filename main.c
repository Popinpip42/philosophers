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

int	main(int argc, char **argv)
{
	//1- n_philos & n_forks 
	//2- time_to_die
	//3- time_to_eat
	//4- time_to_sleep
	//5- n_times_philos_must_eat
	//	if (5) is not specifie,
	//	program ends when a philo dies

  /* TODO: Ideally: (Time to eat = Time to sleep +  Time to think)
   * - (Time to eat - Time to sleep = Time to think)
   *   if (Time to sleep > Time to eat)
   *      - While (thinking)
   *          - time_lost++; (Time lost must be less than Time_to_die)
   * - (Time to eat > Time to die)
   */

  //TODO: implement the data structure for the philos
  //either graph based or list based
  //
  /*  For linked list:
   *  - Each fork/philo is also a t_node
   *  - Each eat(time_to_eat) function:
   *    - calls getForks(prev, next)
   *      - calls getFok(prev) + getFork(next)
   *
   *  //  Dead handling
   *  - Main methods, holds an array
   *    where philos write if they are dead or not
   *  - 
   */

  //TODO: Thread main Algorithm
  // - time_to_eat = time_to_eat;
  // - while (true)
  // -  eat(time_to_sleep)
  // -  sleep(time_to_sleep)
  // -  think(compute_time_to_think(time_to_sleep, time_to_eat))

  //TODO: Shuld i also pass the time_to_eat ...
  /*
  int n = 6;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int times_to_eat;
  */
  t_table *table;
  t_node  *head;
  int     *valid_args;
  int     valid_args_len;

  valid_args = validate_argv(argc, argv, &is_valid_int, &valid_args_len);
  if (!valid_args)
    return (-1);
  print_int_arr(valid_args, valid_args_len);

  table = init_table(valid_args[0]);
  if (!table)
    return (-1);
  printf("Table philos Arg : %d - Bowl : %d\n", table->n_philos, table->shared_bowl);

  //TODO: Pass table to each philo_data
  head = create_table(table->n_philos, valid_args);
  if (head)
  {
    printf("Correctly initialized\n");
    print_table(head);
  }
  else {
    printf("Not correctly initialized\n");
    return (-1);
  }
	
  clear_list(&head);
  if (head == NULL)
    printf("======== CLEANED UP\n");
  else {
    printf("==== head %p\n", head);
    print_node(head);
  }
  free(valid_args);
}

//TODO:
// cc -fsanitize=address -g main.c init_table.c create_table.c split_on.c validate_argv.c validation_func.c strings.c

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

