#include "philo.h"

void	ending_party(t_philo *simInfo)
{
	int	i;

	i = 0;
	while (i < simInfo->_number_of_philosophers)
	{ pthread_detach(simInfo->philos[i]);
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
	int			i;
	pthread_t	*monitor_t = malloc(sizeof(pthread_t));
	pthread_t	*diet_monitor_t = malloc(sizeof(pthread_t));

	if (ac < 5 || ac > 6)
	{
		printf("usage:\n\
(1)number_of_philosophers\n\
(2)time_to_die\n\
(3)time_to_eat\n\
(4)time_to_sleep\n\
(5)(optional)number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	simInfo = get_input(av);
	set_stage(&simInfo);
	i = 0;
	while (i < simInfo._number_of_philosophers)
	{
		simInfo.report[i] = 0;
		if (simInfo.diet)
			simInfo.diet[i] = 0;
		if (pthread_create(&simInfo.philos[i], NULL, routine, (void *)&simInfo))
			exit_fatal("thread create error\n");
		pthread_detach(simInfo.philos[i]);
		i++;
	}
	if (pthread_create(monitor_t, NULL, monitor, (void *)&simInfo))
		exit_fatal("thread create error\n");
	if (simInfo.diet)
		if (pthread_create(diet_monitor_t, NULL, diet_monitor, (void *)&simInfo))
			exit_fatal("thread create error\n");
	pthread_join(*monitor_t, NULL);
	free(monitor_t);
	ending_party(&simInfo);
	return (0);
}
