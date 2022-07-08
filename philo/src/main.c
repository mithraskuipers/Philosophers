/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/07 15:53:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>

/*
1: n philos
2: time it can without food and dies (ms)
3: time it takes to eat (ms)
4: time it takes to sleep (ms)
5: n times must eat
*/

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

int	create_mutexes(t_env *env)
{
	int	i;

	i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	//env->eating_mutex = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	env->eating_mutex = malloc(sizeof(pthread_mutex_t) * 1);
	if (pthread_mutex_init(env->eating_mutex, NULL) == -1)
		return (-1);
	//msg_exit("Error: mutex initialization failed.", 2, 1);
	while (i < env->n_philos)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) == -1)
			return (-1);
		//msg_exit("Error: mutex initialization failed.", 2, 1);
		//if (pthread_mutex_init(&env->eating_mutex[i], NULL) < 0)
		//	msg_exit("Error: mutex initialization failed.", 2, 1);
		i++;
	}
	return (0);
}

// int	init_philos(t_env *env, t_philo **philos)
// {
// 	int	i;

// 	i = 0;
// 	*philos = malloc(env->n_philos * sizeof(t_philo));
// 	if (!philos)
// 		return (-1);
// 	while(i < env->n_philos)
// 	{
// 		(*philos)[i].nbr = i;
// 		(*philos)[i].eating = 0;
// 		(*philos)[i].sleeping = 0;
// 		(*philos)[i].thinking = 0;
// 		(*philos)[i].eat_counter = 0;
// 		(*philos)[i].env = env;
// 		(*philos)[i].fork_left = i;
// 		(*philos)[i].fork_right = (((*philos)[i].nbr + 1) % (*philos)[i].env->n_philos);
// 		i++;
// 	}
// 	return (0);
// }

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
		(*philos)[i].fork_right = (((*philos)[i].nbr + 1) % (*philos)[i].env->n_philos);
		(*philos)[i].last_dinner = get_current_time();
		i++;
	}
	return (0);
}

int	init_threads(t_env *env)
{
	env->threads = malloc(env->n_philos * sizeof(pthread_t));
	if (!env->threads)
		return (-1);
	env->death_check = malloc(sizeof(pthread_t) * 1);
	if (!env->death_check)
		return (-1);
	return (0);
}

void	printer(t_philo *philo, int	task_code)
{
	u_int64_t	time_cur;
	u_int64_t	time;
	time_cur = get_current_time();
	time = time_cur - philo->env->first_dinner;
	time = time_cur;

	pthread_mutex_lock(&philo->env->print_mutex);
	printf("\n"); 
	if (task_code == 0)
		printf("%lu %d has taken a fork\n", time, philo->nbr + 1);
	else if (task_code == 1)
		printf("%lu %d is eating\n", time, philo->nbr + 1);
	else if (task_code == 2)
		printf("%lu %d is sleeping\n", time, philo->nbr + 1);
	else if (task_code == 3)
		printf("%lu %d is thinking\n", time, philo->nbr + 1);
	else if (task_code == 4)
		printf("----------->%lu %d died", time, philo->nbr + 1);
	pthread_mutex_unlock(&philo->env->print_mutex);
	return ;
}

int	is_dead(t_philo *philo)
{
	u_int64_t	current_time;

	current_time = get_current_time();
	if ((current_time - philo->last_dinner) >= (u_int64_t)philo->env->time_die)
	{
		printer(philo, 4);
		return (1);
		//msg_exit("", 2, 1);
		//return (1);
	}
	return (0);
}

int	take_fork(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->nbr % 2 == 0)
	{
		pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
		pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	}
	else
	{
		pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
		pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	}
	printer(philo, FORK);
	printer(philo, FORK);
	return (0);
}

int	return_fork(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
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

int	eating_process(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(philo->env->eating_mutex);
	printer(philo, EAT);
	sleep_for_duration(philo->env->time_eat);
	philo->last_dinner = get_current_time();
	philo->eat_counter++;
	pthread_mutex_unlock(philo->env->eating_mutex);
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	printer(philo, SLEEP);
	sleep_for_duration(philo->env->time_sleep);
	return (0);
}

int	thinking_process(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	printer(philo, THINK);
	usleep(1);
	return (0);
}

void	*cycle(void *philo_object)
{
	t_philo *philo;

	philo = (t_philo *)philo_object;
	while (1)
	{
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

void	*philo_scanner(void *args)
{
	int		i;
	t_env	*env;

	i = 0;
	env = (t_env *)args;
	while (env->someone_died == 0)
	{
		i = 0;
		while (i < env->n_philos)
		{
			if (is_dead(&env->philos[i]))
				return (NULL);
			i++;
		}
		// CHECK N TIMES EAT?
	}
	return (NULL);
}

int	start_threads(t_env *env)
{
	int			i;
	int			status;
	pthread_t	scanner;

	i = 0;
	while (i < env->n_philos)
	{
		status = pthread_create(&env->threads[i], NULL, &cycle, &env->philos[i]);
		if (status != 0)
			return (status); 
		// if (pthread_create(&philos->env->threads[i], NULL, &cycle, &philos[i]) != 0) // philos + i
		// 	msg_exit("Error. Could not create threads.", 2, 1);
		i++;
	}
	status = pthread_create(&scanner, NULL, philo_scanner, env);
	if (status != 0)
		return (status);
		
	//pthread_create(&s_tid, NULL, ft_galina_monitor, (void *)args->all_philos);
	// status = pthread_create(env->death_check, NULL, &death_checker, env);
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
		if (pthread_join(env->threads[philo_nbr], NULL) == -1)
			return (-1);
	}
	return (0);
}

// int	clean_env(t_env *env)
// {
// 	;
// }

// int	clean_philos(t_philo *philos)
// {
// 	;
// }

void	init_env(t_env *env)
{
	env->someone_died = 0;
	env->first_dinner = get_current_time();
	return ;
}

// void	end_threads(t_env *env)
// {
// 	int	nbr_ph;

// 	nbr_ph = env->n_philos;
// 	if (nbr_ph == 1)
// 	{
// 		pthread_mutex_unlock(&env->forks[0]);
// 	}
// 	while (nbr_ph)
// 	{
// 		nbr_ph--;
// 		pthread_join(env->threads[nbr_ph], NULL);
// 	}
// }

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
	//end_threads(env);
	// if (join_threads(env) == -1)
	// 	msg_exit("Error. Could not join threads.", 2, 1);
	printf("FINISHED!<----------------------------------\n");
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