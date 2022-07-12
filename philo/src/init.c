/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 08:52:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 10:59:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_env *env, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(env->n_philos * sizeof(t_philo));
	if (!philos)
		return (-1);
	while(i < env->n_philos)
	{
		(*philos)[i].nbr = i;
		(*philos)[i].eating = 0;
		(*philos)[i].sleeping = 0;
		(*philos)[i].thinking = 0;
		(*philos)[i].eat_counter = 0;
		(*philos)[i].env = env;
		(*philos)[i].fork_left = i;
		(*philos)[i].fork_right = (((*philos)[i].nbr + 1) % \
		(*philos)[i].env->n_philos);
		(*philos)[i].last_dinner = get_current_time();
		(*philos)[i].time_to_die = (*philos)[i].last_dinner + env->time_die;
		(*philos)[i].eating_mutex = malloc(sizeof(pthread_mutex_t) * 1);
		i++;
	}
	return (0);
}

int	init_threads(t_env *env)
{
	env->philo_threads = malloc(env->n_philos * sizeof(pthread_t));
	if (!env->philo_threads)
		return (-1);
	env->life_threads = malloc(env->n_philos * sizeof(pthread_t));
	if (!env->life_threads)
		return (-1);
	// env->death_check = malloc(sizeof(pthread_t) * 1);
	// if (!env->death_check)
	// 	return (-1);
	return (0);
}
