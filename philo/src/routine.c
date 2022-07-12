/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 13:45:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 19:59:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_object)
{
	t_philo *philo;

	philo = (t_philo *)philo_object;
	philo->last_dinner = get_current_time();
	while (1)
	{
		if (philo->eat_counter == philo->env->n_eat)
			philo->done_eating = 1;
		if (take_fork(philo))
			return (NULL);
		if (eating_process(philo))
			return (NULL);
		if (return_fork(philo))
			return (NULL);
		if (sleeping_process(philo))
			return (NULL);
		if (thinking_process(philo))
			return (NULL);
	}
	return (NULL);
}
