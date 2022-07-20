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

/*
volgorde in project maken:
environment struct bedenken/maken
check_input()
parse_input()
check_args()
philo struct bedenken/maken
make_philos()
time_keeping()
sleeping()
eating()
thinking()
death()
create_mutexes()
*/

/* EXPERIMENT */
// int	main(int argc, char **argv)
// {
// 	t_env *env;
// 	env = ft_calloc(1, sizeof(env));
// 	if (!env)
// 		msg_exit("Error: env memory allocated failed.", 2, 1);
// 	if ((argc != 5) && (argc != 6))
// 		msg_exit("Error: Please enter the required number of arguments.", 2, 1);
// 	check_input(argc, argv);
// 	parse_input(argc, argv, env);
// 	check_args(argc, env);
// 	//create_mutexes(env);
// 	//long	tmp;
// 	//tmp = ft_time();
// 	//printf("%ld\n", tmp);
// 	//sleep(1);
// 	//tmp = ft_time();
// 	//printf("%ld\n", tmp);
// 	//t_tv	*get_current_time;
// 	//gettimeofday(get_current_time, NULL);
// 	t_tmpstruct *tmp;
// 	tmp = malloc(sizeof(t_tmpstruct) * 1);
// 	tmp->a = '0';
// 	pthread_mutex_t lock;
// 	pthread_mutex_init(&lock, NULL);
// 	pthread_t	thread_object1;
// 	//pthread_t	thread_object2;
// 	//pthread_t	thread_object3;
// 	pthread_create(&thread_object1, NULL, change_var1, tmp);
// 	//pthread_create(&thread_object2, NULL, change_var2, tmp);
// 	// /pthread_create(&thread_object3, NULL, read_var, tmp);
// 	// pthread_mutex_lock(&lock);
// 	// pthread_mutex_unlock(&lock);
// 	// pthread_join(thread_object1, NULL);
// 	sleep(10);
// 	return (0);
// }
