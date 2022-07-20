int	take_fork(t_philo *philo)
{
	// if (philo->nbr % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	// 	pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	// }
	pthread_mutex_lock(&philo->env->forks[philo->fork_left]);
	pthread_mutex_lock(&philo->env->forks[philo->fork_right]);
	printer(philo, FORK);
	printer(philo, FORK);
	return (0);
}


int	return_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	// if (philo->nbr % 2 == 0)
	// {
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_right]);
	// 	pthread_mutex_unlock(&philo->env->forks[philo->fork_left]);
	// }
	return (0);
}
