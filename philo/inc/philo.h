/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:49:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/09 21:43:20 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // for printf

# include <pthread.h>
# include <sys/time.h>

#define INTMAX 2147483647
#define INTMIN -2147483648

#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIED 4

typedef struct s_philo
{
	int		nbr;
	u_int64_t	last_dinner;
	int		eating;
	int		sleeping;
	int		thinking;
	int		eat_counter;
	int		fork_left;
	int		fork_right;
	pthread_mutex_t *eating_mutex;
	//int		died;
	struct s_env	*env;
}				t_philo;

typedef struct s_env
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	int				someone_died;
	int				dinner_done;
	u_int64_t		first_dinner;
	pthread_t		*philo_threads;
	pthread_t		*life_threads;
	//pthread_t		*death_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eating_mutex;
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

/* time.c */
u_int64_t	sec_to_millisec(u_int64_t sec);
u_int64_t	milli_to_micro(u_int64_t millisec);
u_int64_t	microsec_to_millisec(u_int64_t microsec);
u_int64_t	get_current_time(void);
void	sleep_for_duration(int duration);


# endif
