/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 08:45:39 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/14 09:48:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

	if ((argc != 5) && (argc != 6))
		msg_exit("Error: Please enter the required number of arguments.", 2, 1);
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
