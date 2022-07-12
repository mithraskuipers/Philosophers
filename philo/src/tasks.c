/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 13:52:31 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 14:53:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_process(t_philo *philo)
{
	//pthread_mutex_lock(philo->env->eating_mutex);
	pthread_mutex_lock(philo->eating_mutex);
	printer(philo, EAT);
	philo->eating = 1;
	sleep_for_duration(philo->env->time_eat);
	philo->eating = 0;
	philo->eat_counter++;
	philo->last_dinner = get_current_time();
	philo->time_to_die = philo->last_dinner + philo->env->time_die;
	//printf("\n%d %lu\n\n", philo->nbr, philo->time_to_die);
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
	//usleep(1);
	//exit(1);
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