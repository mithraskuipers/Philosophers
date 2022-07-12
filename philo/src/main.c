/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 15:22:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
1: n philos
2: time it can without food and dies (ms)
3: time it takes to eat (ms)
4: time it takes to sleep (ms)
5: n times must eat
*/

/*
memory leaks
variable clean up
accurate sleep function
*/

int	create_mutexes(t_env *env)
{
	int	i;

	i = 0;
	env->forks = calloc(sizeof(pthread_mutex_t), env->n_philos);
	env->eating_mutex = calloc(1, sizeof(pthread_mutex_t));
	if (pthread_mutex_init(env->eating_mutex, NULL) == -1)
		return (-1);
	//env->print_mutex = calloc(1, sizeof(pthread_mutex_t));
	if (pthread_mutex_init(&env->print_mutex, NULL) == -1)
		return (-1);
	while (i < env->n_philos)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) == -1)
			return (-1);
		i++;
	}
	return (0);
}

// int cleanup

int	is_dead(t_philo *philo)
{
	size_t	current_time;

	current_time = get_current_time();

	pthread_mutex_lock(&philo->env->death_mutex);
	//if ((current_time - philo->last_dinner) > (size_t)philo->env->time_die) // misschien gaat hier iets niet goed
	if (current_time > (philo->last_dinner + philo->env->time_die))
	{
		philo->env->someone_died = 1;
		//printf("\n%d DIED\n", philo->nbr);
		//exit(1);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->death_mutex);
	return (0);
}

void	*philo_scanner(void *philo_object)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)philo_object;
	while (philo->env->someone_died == 0)
	{
		i = 0;
		while (i < philo->env->n_philos)
		{
			if (is_dead(philo))
			{
				printer(philo, 4);
				//exit(1);
				philo->env->someone_died = 1;
				philo->env->continue_dinner = 0;
				return (NULL);
			}
			i++;
		}
		// CHECK N TIMES EAT?
	}
	return (NULL);
}

void	*alive_scanner(void *philo_object)
{
	int i;
	t_philo *philo;
	
	i = 0;
	(void)i;
	philo = (t_philo *)philo_object;
	(void)philo;
	return (NULL);
}

int	start_threads(t_env *env)
{
	int			i;
	int			thread_status;
	int			alive_status;

	i = 0;
	while (i < env->n_philos)
	{
		env->philos[i].last_dinner = get_current_time();
		thread_status = pthread_create(&env->philo_threads[i], NULL, routine, &env->philos[i]); //&env->philos[i]
		if (thread_status != 0)
			return (thread_status); 
		i++;
		usleep(100); // why this?
	}
	i = 0;
	while (i < env->n_philos)
	{
		alive_status = pthread_create(&env->life_threads[i], NULL, philo_scanner, &env->philos[i]); //&env->philos[i]
		if (alive_status != 0)
			return (alive_status); 
		i++;
		usleep(100); // why this?
	}
	return (0);
}

int	join_threads(t_env *env)
{
	int	philo_nbr;

	philo_nbr = env->n_philos;
	// if (philo_nbr == 1)
	// {
	// 	pthread_mutex_unlock(&env->forks[0]); // why 0
	// }
	while (philo_nbr)
	{
		philo_nbr--;
		if (pthread_join(env->philo_threads[philo_nbr], NULL) == -1)
			return (-1);
		if (pthread_join(env->life_threads[philo_nbr], NULL) == -1)
			return (-1);
	}
	return (0);
}

void	init_env(t_env *env)
{
	env->someone_died = 0;
	env->first_dinner = get_current_time();
	env->continue_dinner = 1; 
	return ;
}

void	end_threads(t_env *env)
{
	int	nbr_ph;

	nbr_ph = env->n_philos;
	if (nbr_ph == 1)
	{
		pthread_mutex_unlock(&env->forks[0]);
	}
	while (nbr_ph)
	{
		nbr_ph--;
		pthread_join(env->philo_threads[nbr_ph], NULL);
	}
}

int	main(int argc, char **argv)
{
	t_env	*env;
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		msg_exit("Error: env memory allocated failed.", 2, 1);
	if ((argc != 5) && (argc != 6))
		msg_exit("Error: Please enter the required number of arguments.", 2, 1);
	check_input(argc, argv);
	parse_input(argc, argv, env);
	check_args(argc, env);
	init_env(env);
	if (init_philos(env, &env->philos) == -1)
		msg_exit("Error: Memory allocation for philosophers failed.", 2, 1);
	if (create_mutexes(env) == -1)
		msg_exit("Error: mutex initialization failed.", 2, 1);
	if (init_threads(env) == -1)
		msg_exit("Error: Memory allocation for threads failed.", 2, 1);
	if (start_threads(env) == -1)
		msg_exit("Error. Could not create threads.", 2, 1);
	while (env->continue_dinner)
		continue;
	// end_threads(env);
	// if (join_threads(env) == -1)
	// 	msg_exit("Error. Could not join threads.", 2, 1);
	printf("FINISHED!\n");
}

/*
Come to end when:
	Someone died
	When ate enough times (optional)
*/

/*
TODO:
MAAK DEATH CHECKER NIET EIGEN THREAD, TEVEEL SLOWDOWN
BEDENK IETS ANDERS...
*/

/*
1: n philos
2: time it can without food and dies (ms)
3: time it takes to eat (ms)
4: time it takes to sleep (ms)
5: n times must eat
*/

// TODO!!!!!!
// PRINT FUNCTIE CHECK OF DOOD + MUTEX
// IMPROVED USLEEP()