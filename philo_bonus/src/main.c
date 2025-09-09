#include "../include/philo_bonus.h"

void	print_usage_msg(void)
{
	printf("==== Usage : number_of_philosophers time_to_die time_to_eat ");
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	printf("==== Example : \"5 1 2 3 4\" \"4 3 2 1 \" \n");
	printf("==== (Only Positve numbers allowed) \n");
}

void	clean_all(int *valid_args, t_table **table)
{
	free(valid_args);
	valid_args = NULL;
	clear_table(table);
}

void	philo_routine2(void)
{
	printf("hello world %d\n", getpid());
}

void	wait_procs(pid_t *pids, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			printf("exit status proc : %d - status : %d\n", i, WEXITSTATUS(status));
		i++;
	}
}

void	create_procs(int n, t_table *table, int *valid_args)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * n);
	printf("hello from parent %d\n", getpid());
	i = 0;
	while (i < n)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			philo_routine2();
			clean_all(valid_args, &table);
			free(pids);
			exit(1);
		}
		i++;
	}
	wait_procs(pids, n);
	free(pids);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	//t_node	*head;
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
	create_procs(table->n_philos, table, valid_args);
	clean_all(valid_args, &table);
	return (0);
}
