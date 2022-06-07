/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/07 18:54:31 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
https://github.com/lavrenovamaria/42-philosophers
https://github-com.translate.goog/iciamyplant/Philosophers?_x_tr_sl=auto&_x_tr_tl=en&_x_tr_hl=nl&_x_tr_pto=wapp
*/


#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

int	str_only_nbrs(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && s[i + 1])
		i++;
	else if ((ft_isdigit(s[i]) != 1))
		return (0);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	check_input(int argc, char **argv)
{
	int	arg;
	
	arg = (argc - 1);
	while (arg)
	{
		if (str_only_nbrs(argv[arg]) == 0)
			msg_exit("Error: Provide only numeric arguments.", 2, 1);
		arg--;
	}
}

void	parse_input(int argc, char **argv, t_env *env)
{
	if (mk_atoi(argv[1], &(env->n_philos)))
		msg_exit("Error: mk_atoi() failed.", 2, 1);
	if (mk_atoi(argv[2], &(env->time_die)))
		msg_exit("Error: mk_atoi() failed.", 2, 1);
	if (mk_atoi(argv[3], &(env->time_eat)))
		msg_exit("Error: mk_atoi() failed.", 2, 1);
	if (mk_atoi(argv[4], &(env->time_sleep)))
		msg_exit("Error: mk_atoi() failed.", 2, 1);
	if (argc == 6)
	{
		if (mk_atoi(argv[5], &(env->n_eat)))
			msg_exit("Error: mk_atoi() failed.", 2, 1);
	}
}

void	check_arguments(int argc, t_env *env)
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

	i = 2;
	while (i)
	{
		sleep(1);
		write(1, "2", 1);
		i--;
	}
}

void *print1(void *arg)
{
	int i;
	
	i = 5;
	(void)arg;
	while (i)
	{
		sleep(1);
		write(1, "1", 1);
		i--;
	}
	return (NULL);
}

//#include <pthreads.h> // linux
#include <pthread.h> //macos
#include <sys/time.h>

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	mutex_maker(t_env *env)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_t) * env->n_philos);
	i = 0;
	while (i != env->n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	env->forks = forks;
}


int	main(int argc, char **argv)
{
	t_env *env;

	env = ft_calloc(1, sizeof(env));
	if (!env)
		msg_exit("Error: env memory allocated failed.", 2, 1);
	if ((argc != 5) && (argc != 6))
		msg_exit("Error: Please enter the required number of arguments.", 2, 1);
	check_input(argc, argv);
	parse_input(argc, argv, env);
	check_arguments(argc, env);
	
	long	tmp;
	tmp = ft_time();
	printf("%ld\n", tmp);
	//sleep(1);
	tmp = ft_time();
	printf("%ld\n", tmp);

	//t_tv	*current_time;
	//gettimeofday(current_time, NULL);
	

	//pthread_t	thread_object;
	//pthread_create(&thread_object, NULL, print1, NULL);
	//print2();
	//printf("number of philos: %d", env->n_philos);
	//pthread_join(thread_object, NULL);


	return (0);
}

