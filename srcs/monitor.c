#include "philo.h"

void	philo_message(int nu, char *str, t_philo *simInfo)
{
	if (simInfo->endgame)
		return ;
	pthread_mutex_lock(&simInfo->mtx_cout);
	if (!simInfo->endgame)
		printf("%04ld|philosopher %02d|%s\n",
			timeSinceStart(simInfo->simStartTime), nu, str);
	pthread_mutex_unlock(&simInfo->mtx_cout);
}

int	philo_sleep(t_philo *simInfo, long toWait)
{
	ft_sleep(toWait);
	if (simInfo->endgame)
		return (1);
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*simInfo;
	int		i;

	simInfo = (t_philo *)ptr;
	while (!simInfo->endgame)
	{
		i = 0;
		while (i < simInfo->_number_of_philosophers)
		{
			if (timeSinceStart(simInfo->simStartTime)
				- simInfo->report[i] >= simInfo->_time_to_die)
			{
				pthread_mutex_lock(&simInfo->mtx_cout);
				simInfo->endgame = 1;
				printf("%04ld|philosopher %02d|is DEAD! (last meal %ld)\n",
					timeSinceStart(simInfo->simStartTime),
					i + 1, simInfo->report[i]);
				ft_sleep(simInfo->_time_to_die);
				return (NULL);
			}
			ft_sleep(5);
			i++;
		}
	}
	return (NULL);
}

void	*diet_monitor(void *ptr)
{
	t_philo	*simInfo;

	simInfo = (t_philo *)ptr;
	while (!simInfo->endgame)
	{
		if (simInfo->fed >= simInfo->_number_of_philosophers)
		{
			pthread_mutex_lock(&simInfo->mtx_cout);
			simInfo->endgame = 1;
			printf("%04ld|that's all folks!\n",
				timeSinceStart(simInfo->simStartTime));
			ft_sleep(simInfo->_time_to_die);
			return (NULL);
		}
	}
	return (NULL);
}
