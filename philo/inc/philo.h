/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:49:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/19 22:14:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define INTMAX 2147483647
# define INTMIN -2147483648
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

typedef struct s_philo
{
	int				nbr;
	size_t			last_dinner;
	size_t			time_to_die;
	int				eat_counter;
	int				fork_left;
	int				fork_right;
	int				done_eating;
	pthread_mutex_t	*eating_mutex;
	struct s_env	*env;
}				t_philo;

typedef struct s_env
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	int				n_need_to_eat;
	//int				everyone_alive;
	int				continue_dinner;
	u_int64_t		first_dinner;
	pthread_t		*philo_threads;
	pthread_t		*life_threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}				t_env;

/* random... */
int		ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
void	msg_exit(char *s, int fd, int exit_code);
void	check_input(int argc, char **argv);
void	parse_input(int argc, char **argv, t_env *env);
void	check_args(int argc, t_env *env);
int		iswhitespace(int c);
int		mk_atoi(char *s, int *nbr);

/* tools.c */
int		is_dead(t_philo *philo);
void	msg_exit(char *s, int fd, int exit_code);

/* time.c */
size_t	sec_to_millisec(size_t sec);
size_t	microsec_to_millisec(size_t microsec);
size_t	get_current_time(void);
void	sleep_for_duration(size_t duration);

/* init.c */
void	init_env(t_env *env);
int		init_philos(t_env *env, t_philo **philos);
int		init_threads(t_env *env);

/* printer.c */
void	printer(t_philo *philo, int task_code);

/* tasks.c */
int		eating_process(t_philo *philo);
int		sleeping_process(t_philo *philo);
int		thinking_process(t_philo *philo);
int		take_fork(t_philo *philo);
int		return_fork(t_philo *philo);

/* threads.c */
void	*routine(void *philo_object);
void	*philo_scanner(void *philo_object);
int		start_threads(t_env *env);

#endif
