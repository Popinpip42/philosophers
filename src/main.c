#include "../include/philosophers.h"

void	print_int_arr(int *arr, int len)
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
	printf("==== (Only Positve numbers allowed) \n");
}

//TODO: to free: valid_argv / table / head
int	main(int argc, char **argv)
{
	t_table	*table;
	t_node	*head;
	int		*valid_args;
	int		valid_args_len;

	valid_args = validate_argv(argc, argv, &is_valid_pos_int, &valid_args_len);
	if (!valid_args)
		return (print_usage_msg(), -1);
	printf("Valid_args_len %d\n", valid_args_len);
	//TODO: Create a function that check, that n_philos > 0, and other cases ...
	if (valid_args_len < 4 || valid_args_len > 5)
		return (free(valid_args), print_usage_msg(), -1);
	//print_int_arr(valid_args, valid_args_len);

	table = init_table(valid_args[0]);
	if (!table)
		return (free(valid_args), -1);

	head = create_table(table->n_philos, valid_args, valid_args_len, table);
	if (head)
	{
		printf("Correctly initialized\n");
		print_table(head);
		//table->philo_head_list = head;
	}
	else
	{
		printf("Not correctly initialized\n");
		free(valid_args);
		clear_table(&table);
		return (-1);
	}
	run_simulation(head, table);
	//printf("=== Table time start  in main() : %lu\n", table->start_time);

	clear_list(&head);
	//table->philo_head_list = NULL;
	if (head == NULL)
		printf("======== CLEANED UP\n");
	else
	{
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
//
//TODO: Implement Resource hiarchy solution (avoids deadlock) 
//          + other ROUND ROBIN (avoid starvation)
