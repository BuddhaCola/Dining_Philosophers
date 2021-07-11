# include "philo.h"

#include <stdio.h> //убрать!

void	philo_message(int nu, char *str, t_philo *simInfo)
{
	char	*nustr;
	char	*timestr;

	nustr = ft_itoa(nu);
	timestr = ft_itoa(gettime() - simInfo->simStartTime);
	pthread_mutex_lock(&simInfo->mtx_cout);
	ft_putstr(timestr);
	ft_putstr("| ");
	ft_putstr(nustr);
	ft_putstr("| ");
	ft_putstr(str);
	pthread_mutex_unlock(&simInfo->mtx_cout);
}

void *routine(void *ptr) {
	t_philo *simInfo = (t_philo *)ptr;
	int	nu;
	int	lfork;
	int	rfork;

	pthread_mutex_lock(&simInfo->mtx_cout);
	nu = simInfo->counter;
	simInfo->counter++;
	lfork = nu;
	if (nu == 0)
		rfork = simInfo->_number_of_philosophers - 1;
	else
		rfork = nu - 1;
	pthread_mutex_unlock(&simInfo->mtx_cout);
	while(!simInfo->endgame)
	{
		pthread_mutex_lock(&simInfo->mtx_forks[lfork]);
		// philo_message(nu, "took left fork\n", simInfo);
		pthread_mutex_lock(&simInfo->mtx_forks[rfork]);
		// philo_message(nu, "took right fork\n", simInfo);
		simInfo->report[nu] = gettime();
		ft_sleep(simInfo->_time_to_eat);
		ft_sleep(simInfo->_time_to_sleep);
	}
	return NULL;
}

void ending_party(t_philo *simInfo, )
{
	int i;
	
	i = 0;
	while (i < simInfo._number_of_philosophers)
		if (pthread_mutex_destroy(&simInfo.mtx_forks[i++]))
			exit_fatal("forks destroy error\n");
	if (pthread_mutex_destroy(&simInfo.mtx_cout))
		exit_fatal("cout destroy error\n");
	free(simInfo.mtx_forks);
	free(folks);
	free(simInfo.report);
}

int main (int ac, char **av)
{
	t_philo		simInfo;

	if (ac < 5 || ac > 6)
	{
		printf ("usage:\n\
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
		while (1)
		{
			i = 0;
			while (i < simInfo._number_of_philosophers)
			{
				if (gettime() - simInfo.report[i] >= simInfo._time_to_die)
				{
					simInfo.endgame = 1;
					philo_message(i, "dead!\n", &simInfo);
				}
				i++;
			}
		}
	}
	return (0);
}