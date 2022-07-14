/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 13:45:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/13 19:20:36 by mikuiper      ########   odam.nl         */
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

void	*philo_scanner(void *philo_object)
{
	int i;
	t_philo *philo;

	philo = (t_philo *)philo_object;
	while (philo->env->continue_dinner && !philo->env->someone_died)
	{
		if (philo->env->n_need_to_eat == 0)
			philo->env->continue_dinner = 0;
		i = 0;
		while (i < philo->env->n_philos)
		{
			if (is_dead(philo))
			{
				printer(philo, 4);
				philo->env->someone_died = 1;
				philo->env->continue_dinner = 0;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	start_threads(t_env *env)
{
	int		i;
	int		routine_status;
	int		philo_status;
	i = 0;
	while (i < env->n_philos)
	{
		env->philos[i].last_dinner = get_current_time();
		routine_status = pthread_create(&env->philo_threads[i], NULL, routine, \
		&env->philos[i]);
		if (routine_status != 0)
			return (routine_status); 
		i++;
		//usleep(100);
	}
	i = 0;
	while (i < env->n_philos)
	{
		philo_status = pthread_create(&env->life_threads[i], NULL, \
		philo_scanner, &env->philos[i]);
		if (philo_status != 0)
			return (philo_status); 
		i++;
		//usleep(100);
	}
	return (0);
}
