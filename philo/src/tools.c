/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/03 17:49:03 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/07 17:34:40 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg_exit(char *s, int fd, int exit_code)
{
	if (ft_strlen(s) != 0)
	{
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
	}
	exit(exit_code);
}
