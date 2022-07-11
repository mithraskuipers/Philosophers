/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:37:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/10 11:53:22 by mikuiper      ########   odam.nl         */
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
		i++;
	}
	return (0);
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
		(*philos)[i].eating = 0;
		(*philos)[i].sleeping = 0;
		(*philos)[i].thinking = 0;
		(*philos)[i].eat_counter = 0;
		//(*philos)[i].died = 0;
		(*philos)[i].env = env;
		(*philos)[i].fork_left = i;
		(*philos)[i].fork_right = (((*philos)[i].nbr + 1) % (*philos)[i].env->n_philos);
		(*philos)[i].last_dinner = get_current_time();
		(*philos)[i].time_to_die = (*philos)[i].last_dinner + env->time_die;
		(*philos)[i].eating_mutex = malloc(sizeof(pthread_mutex_t) * 1);
		i++;
	}
	return (0);
}

// TODO!!!!!!
// PRINT FUNCTIE CHECK OF DOOD + MUTEX
// IMPROVED USLEEP()

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

void	printer(t_philo *philo, int	task_code)
{
	size_t	time_cur;
	size_t	time;
	time_cur = get_current_time();
	time = time_cur - philo->env->first_dinner;
	time = time_cur;

	pthread_mutex_lock(&philo->env->print_mutex);

	// size_t	current_time;
	// current_time = get_current_time();
	// printf("\n%d cur:      %zu", philo->nbr, current_time);
	// printf("\n%d thres:    %zu", philo->nbr, philo->last_dinner + philo->env->time_die);
	// printf("\n");
	// printf("\n%d without:  %llu", philo->nbr, current_time - philo->last_dinner);
	//printf("\n%d left:     %llu", philo->nbr, philo->env->time_die - (current_time - philo->last_dinner));
	// printf("\n%d left:     %d", philo->nbr, philo->env->time_die);
	
	// printf("\n%d last dinner:      %zu", philo->nbr, philo->last_dinner);
	// printf("\n%d survive until:    %zu", philo->nbr, philo->time_to_die);
	// printf("\n%d current time:     %zu", philo->nbr, get_current_time());
	// if (philo->time_to_die > get_current_time())
	// 	printf("\n%d should die\n\n", philo->nbr);
	// printf("\n");

	if (!philo->env->someone_died)
	{
		if (task_code == 0)
			printf("%zu %d has taken a fork\n", time, philo->nbr + 1);
		else if (task_code == 1)
			printf("%zu %d is eating\n", time, philo->nbr + 1);
		else if (task_code == 2)
			printf("%zu %d is sleeping\n", time, philo->nbr + 1);
		else if (task_code == 3)
			printf("%zu %d is thinking\n", time, philo->nbr + 1);
		pthread_mutex_unlock(&philo->env->print_mutex);
	}
	else if (philo->env->someone_died && task_code == 4) // dit is niet gegarandeerd de goede kill. Misschien sterven er 2 acher elkaar, en pakt die nu de 2e philo nbr
	{
		printf("%zu %d died\n", time, philo->nbr + 1);
		pthread_mutex_unlock(&philo->env->print_mutex);
	}
	pthread_mutex_unlock(&philo->env->print_mutex);
	return ;
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

int	take_fork(t_philo *philo)
{
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
	//pthread_mutex_lock(philo->env->eating_mutex);
	pthread_mutex_lock(philo->eating_mutex);
	philo->last_dinner = get_current_time();
	printer(philo, EAT);
	philo->eating = 1;
	sleep_for_duration(philo->env->time_eat);
	philo->eating = 0;
	philo->eat_counter++;
	philo->last_dinner = get_current_time();
	philo->time_to_die = philo->last_dinner + philo->env->time_die;
	printf("\n%d %lu\n\n", philo->nbr, philo->time_to_die);
	//is_dead(philo);
	pthread_mutex_unlock(philo->eating_mutex);
	return (0);
}

int	sleeping_process(t_philo *philo)
{
	printer(philo, SLEEP);
	sleep_for_duration(philo->env->time_sleep);
	return (0);
}

int	thinking_process(t_philo *philo)
{
	printer(philo, THINK);
	//usleep(1);
	//exit(1);
	return (0);
}

void	*cycle(void *philo_object)
{
	t_philo *philo;

	philo = (t_philo *)philo_object;
	while (1)
	{
		philo->last_dinner = get_current_time(); // toegevoegd omdat 4 410 200 200 iemand gelijk doodgaat
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

// void	*philo_scanner(void *philo_object)
// {
// 	int i;
// 	t_philo *philo;

// 	i = 0;
// 	philo = (t_philo *)philo_object;
// 	while (philo->env->continue_dinner)
// 	{
// 		printf("%lu\n", get_current_time());
// 		printf("%lu\n\n", philo->time_to_die);
// 		if (!philo->eating && get_current_time() > philo->time_to_die)
// 		{
// 			//pthread_mutex_lock(philo->eating_mutex);
// 			printer(philo, 4);
// 			philo->env->continue_dinner = 0;
// 			philo->env->someone_died = 1;
// 			exit(1);
// 			//pthread_mutex_unlock(philo->eating_mutex);
// 		}	
// 	}
// 	return (NULL);
// }

// void	*alive_scanner(void *philo_object)
// {
// 	int i;
// 	t_philo *philo;
	
// 	i = 0;
// 	philo = (t_philo *)philo_object;
// 	pthread_mutex_lock(philo->eating_mutex);
// 	while (i < philo->env->n_philos)
// 	{
// 		if (is_dead(philo))
// 		{
// 			exit(1);
// 			//printf("HEY");
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }


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
		thread_status = pthread_create(&env->philo_threads[i], NULL, cycle, &env->philos[i]); //&env->philos[i]
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
	// TODO philo_scanner() thread for every philosopher

	// status = pthread_create(&scanner, NULL, philo_scanner, env);
	// if (status != 0)
	// 	return (status);
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
		if (pthread_join(env->philo_threads[philo_nbr], NULL) == -1)
			return (-1);
		if (pthread_join(env->life_threads[philo_nbr], NULL) == -1)
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