/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/05 23:16:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(int argc, char **argv, t_env *env)
{
	mk_atoi(argv[1], &(env->n_philos));
	mk_atoi(argv[2], &(env->time_die));
	mk_atoi(argv[3], &(env->time_eat));
	mk_atoi(argv[4], &(env->time_sleep));
	if (argc == 6)
		mk_atoi(argv[5], &(env->n_eat)); 
}


void	check_input(int argc, t_env *env)
{
	if (env->n_philos < 0)
		msg_exit("Error: Wrong number of philophers.", 2, 1);
	if (env->time_die < 0)
		msg_exit("Error: Wrong time to die.", 2, 1);
	if (env->time_eat < 0)
		msg_exit("Error: Wrong time to eat.", 2, 1);
	if (env->time_sleep < 0)
		msg_exit("Error: Wrong time to sleep.", 2, 1);
	if (argc == 6 && env->n_eat <= 0)
		msg_exit("Error: Wrong number of times everyone should eat.", 2, 1);
}

void print2()
{
	int i;

	i = 10;
	while (i)
	{
		sleep(1);
		write(1, "1", 1);
		i--;
	}
}

void *print1(void *arg)
{
	int i;
	
	i = 10;
	(void)arg;
	while (i)
	{
		sleep(1);
		write(1, "2", 1);
		i--;
	}
	return (NULL);
}

//#include <pthreads.h>

int	main(int argc, char **argv)
{
	t_env *env;

	env = ft_calloc(1, sizeof(env));
	if (!env)
		return (1);
	if ((argc != 5) && (argc != 6))
		msg_exit("Error: Please enter the required program arguments.", 2, 1);
	parse_input(argc, argv, env);
	check_input(argc, env);
	//printf("number of philos: %d", env->n_philos);

	//t_tv	*current_time;
	//gettimeofday(current_time, NULL);
	

	//pthread_t	newthread;
	//pthread_create(&newthread, NULL, print1, NULL);
	//print2();


	return (0);
}

