/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 11:10:56 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/07/12 15:19:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	}
	else if (philo->env->someone_died && task_code == 4) // dit is niet gegarandeerd de goede kill. Misschien sterven er 2 acher elkaar, en pakt die nu de 2e philo nbr
	{
		printf("%zu %d died\n", time, philo->nbr + 1);
		return ;
	}
	pthread_mutex_unlock(&philo->env->print_mutex);
	return ;
}
