/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/13 19:53:33 by mikuiper      ########   odam.nl         */
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
TOEVOEGEN EAT COUNTER CHECK
memory leaks
variable clean up
accurate sleep function
*/

int	create_mutexes(t_env *env)
{
	int	i;

	i = 0;
	env->forks = calloc(sizeof(pthread_mutex_t), env->n_philos);
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
	while (env->continue_dinner || !env->someone_died)
		continue;
	return (0);
}

/*
1: n philos
2: time it can without food and dies (ms)
3: time it takes to eat (ms)
4: time it takes to sleep (ms)
5: n times must eat
*/
