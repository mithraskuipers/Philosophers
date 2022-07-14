/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 08:52:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/13 18:28:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_env(t_env *env)
{
	env->someone_died = 0;
	env->first_dinner = get_current_time();
	env->continue_dinner = 1;
	env->n_need_to_eat = env->n_philos;
	return ;
}

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
		(*philos)[i].eat_counter = 0;
		(*philos)[i].done_eating = 0;
		(*philos)[i].env = env;
		(*philos)[i].fork_left = i;
		(*philos)[i].fork_right = (((*philos)[i].nbr + 1) % \
		(*philos)[i].env->n_philos);
		(*philos)[i].last_dinner = get_current_time();
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
	return (0);
}
