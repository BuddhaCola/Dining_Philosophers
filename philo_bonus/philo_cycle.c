#include "philo.h"

void	update_diet(int nu, t_philo *simInfo, int fed[2])
{
	if (fed[1] == 0)
	{
		fed[0]++;
		if (fed[0] >= simInfo->_number_of_times_each_philosopher_must_eat)
		{
			fed[1] = 1;
			philo_message(nu, "fed_up!", simInfo);
			simInfo->fed++;
		}
	}
}

int	sufferLoop(t_philo *simInfo, int nu, int fed[2])
{
	sem_wait(simInfo->sem_forks);
	philo_message(nu, "take a fork", simInfo);
	sem_wait(simInfo->sem_forks);
	philo_message(nu, "take a fork", simInfo);
	if (!simInfo->endgame)
		simInfo->report[nu - 1] = timeSinceStart(simInfo->simStartTime);
	philo_message(nu, "eat", simInfo);
	philo_sleep(simInfo, simInfo->_time_to_eat);
	sem_post(simInfo->sem_forks);
	sem_post(simInfo->sem_forks);
	if (simInfo->diet)
		update_diet(nu, simInfo, fed);
	philo_message(nu, "go to sleep", simInfo);
	philo_sleep(simInfo, simInfo->_time_to_sleep);
	philo_message(nu, "thinking", simInfo);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*simInfo;
	int		nu;
	int		fed[2];

	fed[0] = 0;
	fed[1] = 0;
	simInfo = (t_philo *)ptr;
	nu = simInfo->counter++ + 1;
	if (nu % 2)
		philo_sleep(simInfo, simInfo->_time_to_eat);
	while (!simInfo->endgame)
		if (sufferLoop(simInfo, nu, fed))
			break ;
	return (NULL);
}
