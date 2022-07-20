/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/05 12:35:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/06/07 17:00:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	size_t			i;
	size_t			len;
	unsigned char	*b_uc;
	unsigned char	c;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	i = 0;
	len = count * size;
	b_uc = (unsigned char *)ptr;
	c = 0;
	while (i < len)
	{
		b_uc[i] = c;
		i++;
	}
	return (ptr);
}

int	iswhitespace(int c)
{
	if ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\r') || (c == '\n') \
	|| (c == '\f'))
		return (1);
	return (0);
}

int	mk_atoi(char *s, int *nbr)
{
	int		i;
	int		sign;
	long	value;

	i = 0;
	while (iswhitespace(s[i]))
		i++;
	value = 0;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		value = (value * 10) + (s[i] - '0');
		if (value > INTMAX || value < INTMIN)
			return (1);
		i++;
	}
	*nbr = (int)value * sign;
	return (0);
}
