# include "philo.h"

void	philo_message(int nu, char *str, t_philo *simInfo)
{
	// char	*nustr;
	// char	*timestr;

	pthread_mutex_lock(&simInfo->mtx_cout);
	// if (!simInfo->endgame)
	{
		printf("%04ld|philosopher %02d|%s\n", timeSinceStart(simInfo->simStartTime), nu + 1, str);
		// nustr = ft_itoa(nu + 1);
		// timestr = ft_itoa(timeSinceStart(simInfo->simStartTime));
		// ft_putstr(timestr);
		// ft_putstr("");
		// ft_putstr(nustr);
		// ft_putstr("");
		// ft_putstr(str);
		// ft_putstr("\n");
		// free(nustr);
		// free(timestr);
	}
	pthread_mutex_unlock(&simInfo->mtx_cout);
}

void *routine(void *ptr) {
	t_philo *simInfo = (t_philo *)ptr;
	int	nu;

	nu = simInfo->counter++;
	while(!simInfo->endgame)
	{
		if (nu % 2)
		{
			pthread_mutex_lock(&simInfo->mtx_forks[nu]);
			philo_message(nu, "took left fork", simInfo);
			if (nu == 0)
				pthread_mutex_lock(&simInfo->mtx_forks[simInfo->_number_of_philosophers - 1]);
			else 
				pthread_mutex_lock(&simInfo->mtx_forks[nu - 1]);
			philo_message(nu, "took right fork", simInfo);

		}
		else
		{
			if (nu == 0)
				pthread_mutex_lock(&simInfo->mtx_forks[simInfo->_number_of_philosophers - 1]);
			else 
				pthread_mutex_lock(&simInfo->mtx_forks[nu - 1]);
			philo_message(nu, "took right fork", simInfo);
			pthread_mutex_lock(&simInfo->mtx_forks[nu]);
			philo_message(nu, "took left fork", simInfo);
		}
		simInfo->report[nu] = timeSinceStart(simInfo->simStartTime) + simInfo->_time_to_die;
		philo_message(nu, "eating", simInfo);
		ft_sleep(simInfo->_time_to_eat);

		pthread_mutex_unlock(&simInfo->mtx_forks[nu]);
		// philo_message(nu, "put down left fork", simInfo);
		if (nu == 0)
			{
				pthread_mutex_unlock(&simInfo->mtx_forks[simInfo->_number_of_philosophers - 1]);
			} else 
			{
				pthread_mutex_unlock(&simInfo->mtx_forks[nu - 1]);
			}
		// philo_message(nu, "put down right fork", simInfo);
		
		philo_message(nu, "fell asleep", simInfo);
		ft_sleep(simInfo->_time_to_sleep);
		philo_message(nu, "thinking", simInfo);
	}
	return NULL;
}

void ending_party(t_philo *simInfo, pthread_t *folks)
{
	// int i;
	
	// i = 0;
	// while (i < simInfo->_number_of_philosophers)
	// 	pthread_mutex_destroy(&simInfo->mtx_forks[i++]);
	// if (pthread_mutex_destroy(&simInfo->mtx_cout))
		// printf("cout destroy|%d\n", pthread_mutex_destroy(&simInfo->mtx_cout));
	free(simInfo->mtx_forks);
	free(folks);
	free(simInfo->report);
}

int main (int ac, char **av)
{
	t_philo		simInfo;

	if (ac < 5 || ac > 6)
	{
		ft_putstr("usage:\n\
(1)number_of_philosophers\n\
(2)time_to_die\n\
(3)time_to_eat\n\
(4)time_to_sleep\n\
(5)(optional)number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	simInfo = get_input(av);
	set_stage(&simInfo);
	int	i = 0;
	while (i < simInfo._number_of_philosophers)
		if (pthread_create(&simInfo.philos[i++], NULL, routine, (void *)&simInfo))
			exit_fatal("thread create error\n");
	{
		int i;

		ft_sleep(simInfo._time_to_eat * 2);
		while (1)
		{
			i = 0;
			while (i < simInfo._number_of_philosophers)
			{
				if (timeSinceStart(simInfo.simStartTime) - simInfo.report[i] >= simInfo._time_to_die)
				{
					{
						pthread_mutex_lock(&simInfo.mtx_cout);
						simInfo.endgame = 1;
						printf("%04ld|philosopher %02d|DEAD!\n", timeSinceStart(simInfo.simStartTime), i + 1);
					}
					ending_party(&simInfo, simInfo.philos);
					exit (0);
				}
				i++;
			}
		}
	}
	return (0);
}
