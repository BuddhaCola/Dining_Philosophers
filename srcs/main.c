# include "philo.h"

void	philo_message(int nu, char *str, t_philo *simInfo)
{
	char	*nustr;
	char	*timestr;

	pthread_mutex_lock(&simInfo->mtx_cout);
	nustr = ft_itoa(nu + 1);
	timestr = ft_itoa(timeSinceStart(simInfo->simStartTime));
	// ft_putstr("⏳");
	ft_putstr(timestr);
	ft_putstr(" ");
	ft_putstr(nustr);
	ft_putstr(" ");
	ft_putstr(str);
	ft_putstr("\n");
	pthread_mutex_unlock(&simInfo->mtx_cout);
	free(nustr);
	free(timestr);
}

void *routine(void *ptr) {
	t_philo *simInfo = (t_philo *)ptr;
	int	nu;
	// int	lfork;
	// int	rfork;

	// pthread_mutex_lock(&simInfo->mtx_cout);
	nu = simInfo->counter++;
	// simInfo->counter++;
	// lfork = nu;
	// if (nu == 0)
	// 	rfork = simInfo->_number_of_philosophers - 1;
	// else
	// 	rfork = nu - 1;
	// pthread_mutex_unlock(&simInfo->mtx_cout);
	while(!simInfo->endgame)
	{
		if (nu % 2)
		{
			pthread_mutex_lock(&simInfo->mtx_forks[nu]);
			philo_message(nu, "took left fork", simInfo);
			if (nu == 0)
			{
				pthread_mutex_lock(&simInfo->mtx_forks[simInfo->_number_of_philosophers - 1]);
			} else 
			{
				pthread_mutex_lock(&simInfo->mtx_forks[nu - 1]);
			}
			philo_message(nu, "took right fork", simInfo);

		}
		else
		{
			if (nu == 0)
			{
				pthread_mutex_lock(&simInfo->mtx_forks[simInfo->_number_of_philosophers - 1]);
			} else 
			{
				pthread_mutex_lock(&simInfo->mtx_forks[nu - 1]);
			}
			philo_message(nu, "took right fork", simInfo);
			pthread_mutex_lock(&simInfo->mtx_forks[nu]);
			philo_message(nu, "took left fork", simInfo);
		}
		simInfo->report[nu] = timeSinceStart(simInfo->simStartTime) + simInfo->_time_to_die;
		philo_message(nu, "eating", simInfo);
		ft_sleep(simInfo->_time_to_eat);

		pthread_mutex_unlock(&simInfo->mtx_forks[nu]);
		philo_message(nu, "put down left fork", simInfo);
		if (nu == 0)
			{
				pthread_mutex_unlock(&simInfo->mtx_forks[simInfo->_number_of_philosophers - 1]);
			} else 
			{
				pthread_mutex_unlock(&simInfo->mtx_forks[nu - 1]);
			}
		philo_message(nu, "put down right fork", simInfo);
		
		philo_message(nu, "fell asleep", simInfo);
		ft_sleep(simInfo->_time_to_sleep);
		philo_message(nu, "thinking", simInfo);
	}
	return NULL;
}

void ending_party(t_philo *simInfo, pthread_t *folks)
{
	int i;
	
	i = 0;
	while (i < simInfo->_number_of_philosophers)
		if (pthread_mutex_destroy(&simInfo->mtx_forks[i++]))
			exit_fatal("forks destroy error\n");
	if (pthread_mutex_destroy(&simInfo->mtx_cout))
		exit_fatal("cout destroy error\n");
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
	pthread_t	*folks = malloc(sizeof(pthread_t) * simInfo._number_of_philosophers); //free!
	{
		int i;

		i = 0;
		while (i < simInfo._number_of_philosophers) {
			if (pthread_create(&folks[i++], NULL, routine, (void *)&simInfo))
				exit_fatal("thread create error\n");
		}
	}

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
					philo_message(i+1, "dead!💀", &simInfo);
					simInfo.endgame = 1;
					return (0);
				}
				i++;
			}
		}
	}
	return (0);
}