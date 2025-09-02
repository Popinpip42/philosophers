/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:36 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:40:37 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (get_time_ms() < start_time)
		continue ;
}

void	ft_sleep(t_table *table, long time_to_sleep)
{
	unsigned long	end;
	unsigned long	now;
	unsigned long	time_left;

	end = get_time_ms() + time_to_sleep;
	while (get_state(table))
	{
		now = get_time_ms();
		if (now >= end)
			break ;
		time_left = end - now;
		if (time_left > 2)
			usleep(1000);
		else
			usleep(100);
	}
}
