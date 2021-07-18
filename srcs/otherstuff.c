#include "philo.h"

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

void	ft_sleep(int msToSleep)
{
	long	start;

	start = gettime();
	while (1)
	{
		usleep(60);
		if (gettime() - start >= msToSleep)
			return ;
	}
}

int	get_input(int ac, char *argv[], t_philo *simInfo)
{
	if (ac < 5 || ac > 6)
	{
		printf("usage:\n\
(1)number_of_philosophers\n\
(2)time_to_die\n\
(3)time_to_eat\n\
(4)time_to_sleep\n\
(5)(optional)number_of_times_each_philosopher_must_eat\n");
		return (1);
	}
	memset(simInfo, 0, sizeof(t_philo));
	simInfo->_number_of_philosophers = ft_atoi(argv[1]);
	simInfo->_time_to_die = ft_atoi(argv[2]);
	simInfo->_time_to_eat = ft_atoi(argv[3]);
	simInfo->_time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simInfo->_number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (simInfo->_number_of_philosophers <= 0
		|| simInfo->_time_to_die <= 0
		|| simInfo->_time_to_eat <= 0
		|| simInfo->_time_to_sleep <= 0
		|| (argv[5]
			&& simInfo->_number_of_times_each_philosopher_must_eat <= 0))
	{
		printf("wrong input!\n");
		return (1);
	}
	return (0);
}

void	set_stage(t_philo *simInfo)
{
	int	i;

	simInfo->counter = 0;
	simInfo->simStartTime = gettime();
	simInfo->mtx_forks = malloc(sizeof(pthread_mutex_t)
			* simInfo->_number_of_philosophers);
	pthread_mutex_init(&simInfo->mtx_cout, NULL);
	simInfo->report = malloc(sizeof(int) * simInfo->_number_of_philosophers);
	simInfo->endgame = 0;
	if (simInfo->_number_of_times_each_philosopher_must_eat)
		simInfo->diet = malloc(sizeof(int) * simInfo->_number_of_philosophers);
	i = 0;
	while (i < simInfo->_number_of_philosophers)
	{
		pthread_mutex_init(&simInfo->mtx_forks[i++], NULL);
	}
	simInfo->philos
		= malloc(sizeof(pthread_t) * simInfo->_number_of_philosophers);
}

int	threads_creation(t_philo *simInfo)
{
	int			i;

	i = 0;
	while (i < simInfo->_number_of_philosophers)
	{
		simInfo->report[i] = 0;
		if (simInfo->diet)
			simInfo->diet[i] = 0;
		if (pthread_create(&simInfo->philos[i],
				NULL, routine, (void *)simInfo))
			return (1);
		pthread_detach(simInfo->philos[i]);
		i++;
	}
	return (0);
}
