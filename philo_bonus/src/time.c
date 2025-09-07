#include "../include/philo_bonus.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (res);
}

void	start_delay(long start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

/*
int	ft_sleep(t_table *table, long time_to_sleep)
{
	unsigned long	end;
	unsigned long	now;
	long			remaining;

	end = get_time_ms() + time_to_sleep;
	while (get_state(table))
	{
		now = get_time_ms();
		if (now >= end)
			break ;
		remaining = end - now;
		if (remaining > 2)
			usleep(1000);
		else
			usleep(100);
	}
	return (!get_state(table));
}
*/
