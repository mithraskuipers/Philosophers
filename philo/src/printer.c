/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 11:10:56 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/19 22:13:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(t_philo *philo, int task_code)
{
	size_t	time;

	time = get_current_time() - philo->env->first_dinner;
	pthread_mutex_lock(&philo->env->print_mutex);
	//if (philo->env->everyone_alive)
	if (philo->env->continue_dinner)
	{
		if (task_code == 0)
			printf("%zu %d has taken a fork\n", time, philo->nbr + 1);
		else if (task_code == 1)
			printf("%zu %d is eating\n", time, philo->nbr + 1);
		else if (task_code == 2)
			printf("%zu %d is sleeping\n", time, philo->nbr + 1);
		else if (task_code == 3)
			printf("%zu %d is thinking\n", time, philo->nbr + 1);
	}
	else if (task_code == 4)
	{
		printf("%zu %d died\n", time, philo->nbr + 1);
	}
	pthread_mutex_unlock(&philo->env->print_mutex);
	return ;
}
