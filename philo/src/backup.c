/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/23 17:20:09 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
https://github.com/lavrenovamaria/42-philosophers
https://github-com.translate.goog/iciamyplant/Philosophers?_x_tr_sl=auto&_x_tr_tl=en&_x_tr_hl=nl&_x_tr_pto=wapp
*/

#include "philo.h"


#include <pthread.h>
#include <sys/time.h>

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

u_int64_t	sec_to_millisec(u_int64_t sec)
{
	u_int64_t	millisec;
	
	millisec = sec * 1000;
	return (millisec);
}

u_int64_t	milli_to_micro(u_int64_t millisec)
{
	u_int64_t	microsec;
	
	microsec = millisec * 1000;
	return (microsec);
}

u_int64_t	microsec_to_millisec(u_int64_t microsec)
{
	u_int64_t	millisec;
	
	millisec = microsec / 1000;
	return (millisec);
}

void	create_mutexes(t_env *env)
{
	int	i;

	i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	env->eating = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	while (i < env->n_philos)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) < 0)
			msg_exit("Error: mutex initialization failed.", 2, 1);
		if (pthread_mutex_init(&env->eating[i], NULL) < 0)
			msg_exit("Error: mutex initialization failed.", 2, 1);
		i++;
	}
}

// long	ft_time(void)
// {
// 	struct timeval	tv;
// 	long			res;

// 	gettimeofday(&tv, NULL);
// 	// tv gives seconds calculation since the epoch. tv_sec seconds, tv_usec microseconds (additional)
// 	res = 1000 * (u_int64_t)tv.tv_sec; // times 1000 for sec->millisec)
// 	res = res + (u_int64_t)tv.tv_usec / 1000;
// 	return (res);
// }

u_int64_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return(sec_to_millisec(tv.tv_sec) + microsec_to_millisec(tv.tv_usec));
}

void	printer(t_philo *philo, int	task_code)
{
	u_int64_t	time;
	time = get_current_time();
	if (task_code == 0)
		printf("%lu %d has taken a fork\n", time, philo->nbr);
	else if (task_code == 1)
		printf("%lu %d is eating\n", time, philo->nbr);
	else if (task_code == 2)
		printf("%lu %d is sleeping\n", time, philo->nbr);
	else if (task_code == 3)
		printf("%lu %d is thinking\n", time, philo->nbr);
	else if (task_code == 4)
		printf("%lu %d died\n", time, philo->nbr);
	return ;
}

void	sleeping(size_t duration)
{
	size_t	stopping_time;

	stopping_time =  get_current_time() + duration;
	while (get_current_time() < stopping_time)
		usleep(milli_to_micro(duration));
	return ;
}

void	init_philos(t_env *env, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(env->n_philos * sizeof(t_philo));
	if (!philos)
		msg_exit("Error: Memory allocation for philosophers failed.", 2, 1);
	while(i < env->n_philos)
	{
		(*philos)[i].nbr = i;
		(*philos)[i].eating = 0;
		(*philos)[i].sleeping = 0;
		(*philos)[i].thinking = 0;
		(*philos)[i].env = env;
		i++;
	}
	return ;
}

void	init_threads(t_env *env)
{
	env->threads = malloc(env->n_philos * sizeof(pthread_t));
	if (!env->threads)
		msg_exit("Error: Memory allocation for threads failed.", 2, 1);
	return ;
}

void	init_time(t_env *env)
{
	env->first_dinner = get_current_time();
	return ;
}

void	eating_process(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->nbr;
	right_fork = ((philo->nbr + 1) % philo->env->n_philos);
	pthread_mutex_lock(&philo->env->forks[left_fork]);
	printer(philo, FORK);
	pthread_mutex_lock(&philo->env->forks[right_fork]);
	printer(philo, FORK);
	printer(philo, EAT);
	philo->last_dinner = get_current_time();

	//usleep(milli_to_micro(philo->env->time_eat));

	pthread_mutex_unlock(&philo->env->forks[left_fork]);
	pthread_mutex_unlock(&philo->env->forks[right_fork]);	

}


void	sleeping_process(t_philo *philo)
{
	printer(philo, SLEEP);
	sleeping(philo->env->time_sleep);
	return ;
}

void	thinking_process(t_philo *philo)
{
	printer(philo, THINK);
	return ;
}

void	*cycle(void *philo_object)
{
	while (1)
	{
		t_philo *philo; 
		philo = (t_philo *)philo_object;
		eating_process(philo);
		thinking_process(philo);
		sleeping_process(philo);
	}
	return NULL;
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

	t_philo *philos;
	init_philos(env, &philos);
	create_mutexes(env);
	init_threads(env);

	int	i;
	i = 0;
	while (i < env->n_philos)
	{
		if (pthread_create(&env->threads[i], NULL, &cycle, &philos[i]) != 0) // philos + i
			msg_exit("Error. Could not create threads.", 2, 1);
		i++;
	}
	printf("FINISHED!<----------------------------------\n");
}




// void	pick_fork(t_philo *philo)
// {
// 	int	left_fork;
// 	int	right_fork;

// 	// left_fork = philo->nbr;
// 	// right_fork = ((philo->nbr + 1) % philo->env->n_philos);
// 	printer(philo, FORK);
// 	if (philo->nbr % 2 == 0)
// 		pthread_mutex_lock(&philo->env->forks[right_fork]);
// 	else
// 		pthread_mutex_lock(&philo->env->forks[left_fork]);
// 	printer(philo, FORK);
// }

// void	pick_fork(t_philo *philo)
// {
// // 	int	left_fork;
// // 	int	right_fork;
// 	// left_fork = philo->nbr;
// 	// right_fork = ((philo->nbr + 1) % philo->env->n_philos);
// 	printer(philo, FORK);
// 	if (philo->nbr % 2 == 0)
// 		pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
// 	else
// 		pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
// 	printer(philo, FORK);
// }

// void	return_fork(t_philo *philo)
// {
	// int	left_fork;
	// int	right_fork;

	// left_fork = philo->nbr;
	// right_fork = ((philo->nbr + 1) % philo->env->n_philos);
	// if (philo->nbr % 2 == 0)
	// 	pthread_mutex_unlock(&philo->env->forks[left_fork]);
	// else
	// 	pthread_mutex_lock(&philo->env->forks[right_fork]);
// }

// long	ft_time(void)
// {
// 	struct timeval	tv;
// 	long			res;

// 	gettimeofday(&tv, NULL);
// 	// tv gives seconds calculation since the epoch. tv_sec seconds, tv_usec microseconds (additional)
// 	res = 1000 * (u_int64_t)tv.tv_sec; // times 1000 for sec->millisec)
// 	res = res + (u_int64_t)tv.tv_usec / 1000;
// 	return (res);
// }

	//int	left_fork;
	//int	right_fork;

	//left_fork = philo->nbr;
	//right_fork = ((philo->nbr + 1) % philo->env->n_philos);
	//pthread_mutex_lock(&philo->env->forks[left_fork]);
	//printer(philo, FORK);
	//pthread_mutex_lock(&philo->env->forks[right_fork]);
	//printer(philo, FORK);
	//usleep(milli_to_micro(philo->env->time_eat)); // waiting
	//usleep(milli_to_micro(philo->env->time_eat)); // waiting
	//pthread_mutex_unlock(&philo->env->forks[left_fork]);
	//pthread_mutex_unlock(&philo->env->forks[right_fork]);