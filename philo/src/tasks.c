/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 13:52:31 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 19:57:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_process(t_philo *philo)
{
	pthread_mutex_lock(philo->eating_mutex);
	printer(philo, EAT);
	sleep_for_duration(philo->env->time_eat);
	//philo->eat_counter++;
	philo->last_dinner = get_current_time();
	philo->time_to_die = philo->last_dinner + philo->env->time_die;
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
	if (philo->nbr % 2 == 0)
	{
		pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
		pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	}
	else
	{
		pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
		pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	}
	return (0);
}