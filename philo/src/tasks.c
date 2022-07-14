/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 13:52:31 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/13 18:27:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_process(t_philo *philo)
{
	pthread_mutex_lock(philo->eating_mutex);
	printer(philo, EAT);
	sleep_for_duration(philo->env->time_eat);
	philo->last_dinner = get_current_time();
	philo->eat_counter++;
	if (philo->done_eating == 0)
	{
		if (philo->eat_counter == philo->env->n_eat)
		{
			philo->done_eating = 1;
			philo->env->n_need_to_eat = philo->env->n_need_to_eat - 1;
		}
	}
	pthread_mutex_unlock(philo->eating_mutex);
	return (0);
}

int	sleeping_process(t_philo *philo)
{ 
	printer(philo, SLEEP);
	sleep_for_duration(philo->env->time_sleep);
	return (0);
}

int	thinking_process(t_philo *philo)
{
	printer(philo, THINK);
	return (0);
}

int	take_fork(t_philo *philo)
{
	// if (philo->nbr % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	// }
	pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	printer(philo, FORK);
	printer(philo, FORK);
	return (0);
}

int	return_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	// if (philo->nbr % 2 == 0)
	// {
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	// }
	return (0);
}