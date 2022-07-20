/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:49:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/19 22:14:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->death_mutex);
	if (get_current_time() > (philo->last_dinner + philo->env->time_die))
	{
		//philo->env->everyone_alive = 0;
		philo->env->continue_dinner = 0;
		//printer(philo, 4);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death_mutex);
	return (0);
}

void	msg_exit(char *s, int fd, int exit_code)
{
	if (ft_strlen(s) != 0)
	{
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
	}
	exit(exit_code);
}
