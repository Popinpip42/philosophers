#include "../include/philosophers.h"

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
	//printf("%s\n", __FUNCTION__);
	while (get_time_ms() < start_time)
		continue ;
	//printf("%s line : %d\n", __FUNCTION__, __LINE__);
}

void	ft_sleep(t_table *table, long time_to_sleep)
{
	long	wake_up;

	wake_up = get_time_ms() + time_to_sleep;
	while (get_time_ms() < wake_up)
	{
		if (!get_state(table))
			break ;
		usleep(100);
	}
}
