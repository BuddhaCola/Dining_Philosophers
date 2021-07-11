#include "philo.h"

long	gettime()
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

void	ft_sleep(int msec)
{
	long	waketime;

	waketime = gettime() + msec;
	while (1) {
		if (gettime() >= waketime)
			return;
	}
}


t_philo	get_input(char *argv[])
{
	t_philo	simInfo;

	simInfo.counter = 0;
	simInfo.simStartTime = gettime();
	simInfo._number_of_philosophers = ft_atoi(argv[1]);
	simInfo._time_to_die = ft_atoi(argv[2]);
	simInfo._time_to_eat = ft_atoi(argv[3]);
	simInfo._time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simInfo.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	simInfo.mtx_forks = malloc(sizeof(pthread_mutex_t) * simInfo._number_of_philosophers);
	pthread_mutex_init(&simInfo.mtx_cout, NULL);
	int i;

	i = 0;
	while (i < simInfo._number_of_philosophers)
		pthread_mutex_init(&simInfo.mtx_forks[i++], NULL);
	return (simInfo);
}