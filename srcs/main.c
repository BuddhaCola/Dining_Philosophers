#include "philo.h"

void	ending_party(t_philo *simInfo)
{
	int	i;

	i = 0;
	while (i < simInfo->_number_of_philosophers)
	{
		pthread_detach(simInfo->philos[i]);
		pthread_mutex_destroy(&simInfo->mtx_forks[i++]);
	}
	pthread_mutex_destroy(&simInfo->mtx_cout);
	free(simInfo->mtx_forks);
	free(simInfo->report);
	free(simInfo->philos);
	if (simInfo->_number_of_times_each_philosopher_must_eat)
		free(simInfo->diet);
}

int	main(int ac, char **av)
{
	t_philo		simInfo;
	pthread_t	*monitor_t;
	pthread_t	*diet_monitor_t;

	monitor_t = malloc(sizeof(pthread_t));
	diet_monitor_t = malloc(sizeof(pthread_t));
	if (get_input(ac, av, &simInfo))
		return (0);
	set_stage(&simInfo);
	if (threads_creation(&simInfo))
		return (1);
	if (pthread_create(monitor_t, NULL, monitor, (void *)&simInfo))
		exit_fatal("thread create error\n");
	if (simInfo.diet)
		if (pthread_create(diet_monitor_t, NULL,
				diet_monitor, (void *)&simInfo))
			exit_fatal("thread create error\n");
	pthread_join(*monitor_t, NULL);
	free(monitor_t);
	ending_party(&simInfo);
	return (0);
}
