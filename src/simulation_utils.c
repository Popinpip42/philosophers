#include "../include/philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (res);
}

void	print_trace(t_table *table, int id, long time, char *msg)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%lu ID: %d %s\n", time - table->start_time, id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}


