/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/01 16:09:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 19:37:44 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	sec_to_millisec(size_t sec)
{
	size_t	millisec;
	
	millisec = sec * 1000;
	return (millisec);
}

size_t	microsec_to_millisec(size_t microsec)
{
	size_t	millisec;
	
	millisec = microsec / 1000;
	return (millisec);
}

size_t	get_current_time(void)
{
	struct timeval	tv;
	size_t	current_time;

	gettimeofday(&tv, NULL);
	current_time = (size_t)sec_to_millisec(tv.tv_sec) + \
	microsec_to_millisec(tv.tv_usec);
	return(current_time);
}

void	sleep_for_duration(size_t duration)
{
	size_t	start_time;

	start_time = 0;
	start_time = get_current_time();
	while ((get_current_time() - start_time) < duration)
		usleep(duration / 10);
}
