#include "philo.h"

void *monitor(void *ptr)
{
	t_philo *simInfo;
	int		i;

	simInfo = (t_philo *)ptr;
	while (!simInfo->endgame)
	{
		i = 0;
		while (i < simInfo->_number_of_philosophers)
		{
			if (timeSinceStart(simInfo->simStartTime) - simInfo->report[i] >= simInfo->_time_to_die)
			{
					pthread_mutex_lock(&simInfo->mtx_cout);
					simInfo->endgame = 1;
					printf("%04ld|philosopher %02d|is DEAD! (last meal %ld)\n", timeSinceStart(simInfo->simStartTime), i + 1, simInfo->report[i]);
					ft_sleep(simInfo->_time_to_die);
					return NULL;
			}
			ft_sleep(5);
			i++;
		}
	}
	return NULL;
}

void *diet_monitor(void *ptr)
{
	t_philo *simInfo;

	simInfo = (t_philo *)ptr;
	while (!simInfo->endgame)
	{
		if (simInfo->fed >= simInfo->_number_of_philosophers)
		{
			pthread_mutex_lock(&simInfo->mtx_cout);
			simInfo->endgame = 1;
			printf("%04ld|that's all folks!\n", timeSinceStart(simInfo->simStartTime));
			ft_sleep(simInfo->_time_to_die);
			return NULL;
		}
	}
	return NULL;
}
