#include "../include/philo_bonus.h"

void	print_usage_msg(void)
{
	printf("==== Usage : number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	printf("==== Example : \"5 1 2 3 4\" \"4 3 2 1 \" \n");
	printf("==== (Only Positve numbers allowed) \n");
}

void	clean_all(t_node **head, int *valid_args, t_table **table)
{
	clear_list(head);
	free(valid_args);
	valid_args = NULL;
	clear_table(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_node	*head;
	int		*valid_args;
	int		valid_args_len;

	valid_args = validate_argv(argc, argv, &is_valid_pos_int, &valid_args_len);
	if (!valid_args)
		return (print_usage_msg(), -1);
	if (valid_args_len < 4 || valid_args_len > 5)
		return (free(valid_args), print_usage_msg(), -1);
	table = init_table(valid_args[0]);
	if (!table)
		return (free(valid_args), -1);
	head = create_table(table->n_philos, valid_args, valid_args_len, table);
	if (!head)
	{
		printf("Not correctly initialized\n");
		free(valid_args);
		clear_table(&table);
		return (-1);
	}
	//run_simulation(head, table);
	clean_all(&head, valid_args, &table);
	return (0);
}
