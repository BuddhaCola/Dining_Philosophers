#include "philo.h"

void	whatTheFork(t_philo *simInfo, int nu, int (*fun)(pthread_mutex_t *))
{
	fun(&simInfo->mtx_forks[nu]);
	if (fun == pthread_mutex_lock)
		philo_message(nu, "took left fork", simInfo);
	if (simInfo->_number_of_philosophers == 1)
		ft_sleep(simInfo->_time_to_die);
	else
	{
		if (nu == simInfo->_number_of_philosophers)
			fun(&simInfo->mtx_forks[1]);
		else
			fun(&simInfo->mtx_forks[nu + 1]);
		if (fun == pthread_mutex_lock && simInfo->_number_of_philosophers > 1)
			philo_message(nu, "took right fork", simInfo);
	}
}

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
	whatTheFork(simInfo, nu, &pthread_mutex_lock);
	if (simInfo->endgame)
		return (1);
	if (!simInfo->endgame)
		simInfo->report[nu - 1] = timeSinceStart(simInfo->simStartTime);
	philo_message(nu, "eat", simInfo);
	if (philo_sleep(simInfo, simInfo->_time_to_eat))
		return (1);
	whatTheFork(simInfo, nu, &pthread_mutex_unlock);
	if (simInfo->diet)
		update_diet(nu, simInfo, fed);
	philo_message(nu, "go to sleep", simInfo);
	if (philo_sleep(simInfo, simInfo->_time_to_sleep))
		return (1);
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
		if (philo_sleep(simInfo, simInfo->_time_to_eat))
			return (NULL);
	while (!simInfo->endgame)
		if (sufferLoop(simInfo, nu, fed))
			break ;
	return (NULL);
}
