#include "philosophers.h"

int	main(int argc, char **argv)
{
	//1- n_philos & n_forks 
	//2- time_to_die 
	//3- time_to_eat
	//4- time_to_sleep
	//5- n_times_philos_must_eat
	//	if (5) is not specifie,
	//	program ends when a philo dies
	
	
}

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























