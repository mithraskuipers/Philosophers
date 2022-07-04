/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 16:09:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/01 16:11:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	sec_to_millisec(u_int64_t sec)
{
	u_int64_t	millisec;
	
	millisec = sec * 1000;
	return (millisec);
}

u_int64_t	milli_to_micro(u_int64_t millisec)
{
	u_int64_t	microsec;
	
	microsec = millisec * 1000;
	return (microsec);
}

u_int64_t	microsec_to_millisec(u_int64_t microsec)
{
	u_int64_t	millisec;
	
	millisec = microsec / 1000;
	return (millisec);
}

u_int64_t	get_current_time(void)
{
	struct timeval	tv;
	u_int64_t		current_time;

	gettimeofday(&tv, NULL);
	current_time = (u_int64_t)sec_to_millisec(tv.tv_sec) + microsec_to_millisec(tv.tv_usec);
	return(current_time);
}

void	sleep_for_duration(int duration)
{
	size_t	stopping_time;

	stopping_time = get_current_time() + duration;
	while (get_current_time() < stopping_time)
		usleep(1);
}
