/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:49:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/07 18:55:41 by mikuiper      ########   odam.nl         */
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

typedef struct s_env
{
	int	n_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	n_eat;
	pthread_mutex_t	*forks;
}				t_env;

typedef struct s_philo
{
	int	id;
	int	eat;
	int	sleep;
	int	think;
	
}				t_philo;



int		ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
void	msg_exit(char *s, int fd, int exit_code);
void	check_input(int argc, char **argv);
void	parse_input(int argc, char **argv, t_env *env);
void	check_params(int argc, t_env *env);
int		iswhitespace(int c);
int		mk_atoi(char *s, int *nbr);

# endif
