/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/11 13:27:26 by mikuiper      ########   odam.nl         */
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

void	check_args(int argc, t_env *env)
{
	if (env->n_philos < 0)
		msg_exit("Error: Need at least 1 philosopher..", 2, 1);
	if (env->time_die < 0)
		msg_exit("Error: Wrong time to die.", 2, 1);
	if (env->time_eat < 0)
		msg_exit("Error: Wrong time to eat.", 2, 1);
	if (env->time_sleep < 0)
		msg_exit("Error: Wrong time to sleep.", 2, 1);
	if (argc == 6 && env->n_eat <= 0)
		msg_exit("Error: Wrong number of times everyone should eat.", 2, 1);
}

void printer(char n)
{
	int i;
	
	i = 0;
	while (i < 4)
	{
		write(1, &n, 1);
		write(1,"\n", 1);
		i++;
		sleep(1);
	}
}

void player2(void)
{
	printer('2');
}

void player3(void)
{
	printer('3');
}

void *player1(void *arg)
{
	(void)arg;
	printer('1');
	return NULL;
}

void *player4(void *arg)
{
	(void)arg;
	printer('4');
	return NULL;
}

//#include <pthreads.h> // linux
#include <pthread.h> //macos
#include <sys/time.h>

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	// tv gives seconds calculation since the epoch. tv_sec seconds, tv_usec microseconds (additional)
	res = 1000 * (size_t)tv.tv_sec; // times 1000 for sec->millisec)
	res = res + (size_t)tv.tv_usec / 1000;
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

long long	sec_to_millisec(int sec)
{
	long long	millisec;
	
	millisec = sec * 1000;
	return (millisec);
}

long long	microsec_to_millisec(int microsec)
{
	long long	millisec;
	
	millisec = microsec / 1000;
	return (millisec);
}

void	create_mutex(t_env *env)
{
	int	i;

	i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	env->eating = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	while (i < env->n_philos)
	{
		pthread_mutex_init(env->forks[i], NULL);
		pthread_mutex_init(env->eating[i], NULL);
		
	}
}

// int	main(int argc, char **argv)
// {
// 	t_env *env;

// 	env = ft_calloc(1, sizeof(env));
// 	if (!env)
// 		msg_exit("Error: env memory allocated failed.", 2, 1);
// 	if ((argc != 5) && (argc != 6))
// 		msg_exit("Error: Please enter the required number of arguments.", 2, 1);
// 	check_input(argc, argv);
// 	parse_input(argc, argv, env);
// 	check_args(argc, env);
	
// 	//create_mutex(env);

// 	//long	tmp;
// 	//tmp = ft_time();
// 	//printf("%ld\n", tmp);
// 	//sleep(1);
// 	//tmp = ft_time();
// 	//printf("%ld\n", tmp);
// 	//t_tv	*current_time;
// 	//gettimeofday(current_time, NULL);

// 	t_tmpstruct *tmp;
// 	tmp = malloc(sizeof(t_tmpstruct) * 1);
// 	tmp->a = '0';

// 	pthread_mutex_t lock;
// 	pthread_mutex_init(&lock, NULL);
// 	pthread_t	thread_object1;
// 	//pthread_t	thread_object2;
// 	//pthread_t	thread_object3;
// 	pthread_create(&thread_object1, NULL, change_var1, tmp);
// 	//pthread_create(&thread_object2, NULL, change_var2, tmp);
// 	// /pthread_create(&thread_object3, NULL, read_var, tmp);
// 	// pthread_mutex_lock(&lock);
// 	// pthread_mutex_unlock(&lock);
// 	// pthread_join(thread_object1, NULL);
// 	sleep(10);

// 	return (0);
// }
