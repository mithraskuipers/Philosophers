/*
// practice with threads and mutex
int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        // read mails
        // increment
        // write mails
    }
	return NULL;
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
        return 2;
    }
    if (pthread_create(&p3, NULL, &routine, NULL) != 0) {
        return 3;
    }
    if (pthread_create(&p4, NULL, &routine, NULL) != 0) {
        return 4;
    }

    if (pthread_join(p1, NULL) != 0) {
        return 5;
    }
    if (pthread_join(p2, NULL) != 0) {
        return 6;
    }
    if (pthread_join(p3, NULL) != 0) {
        return 7;
    }
    if (pthread_join(p4, NULL) != 0) {
        return 8;
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}
*/


// werkt!
// void	init_philos(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	t_philo *philos;
// 	philos = malloc(sizeof(t_philo) * (env->n_philos));
// 	//protect
// 	while(i < env->n_philos)
// 	{
// 		philos[i].nbr = i;
// 		printf("%d\n", philos[i].nbr);
// 		i++;
// 	}
// }

/*
// werkt, maar kut want 0 index werkt niet.
// moet werken met dubbele pointers
void	init_philos(t_env *env)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	env->philos = malloc((sizeof(t_philo) * (env->n_philos)));
	if (!env->philos)
		exit(1); // rough
	while(i <= env->n_philos)
	{
		env->philos[i].nbr = j;
		printf("%d\n", env->philos[i].nbr);
		i++;
		j++;
	}
}
*/

// int	init_philos(t_env *env)
// {
// 	int	i;

// 	env->philos = malloc(sizeof(t_philo) * env->n_philos);
// 	//env->forks = malloc(sizeof(int) * env->n_philos);
// 	//if (!env->philos || !env->forks)
// 	//	return (ft_log(MALLOC_ERROR));
// 	i = 0;
// 	while (i < env->n_philos)
// 	{
// 		env->philos[i].nbr = 0;
// 		//env->forks[i] = 0;
// 		//env->philos[i].position = i;
// 		//env->philos[i].l_fork = i;
// 		//env->philos[i].r_fork = (i + 1) % env->amount;
// 		//env->philos[i].meals = 0;
// 		//env->philos[i].eating = 0;
// 		//env->philos[i].env = env;
// 		i++;
// 	}
// 	return (0);
// }
