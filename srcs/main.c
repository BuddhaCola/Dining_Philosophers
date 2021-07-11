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
	printf("%d locked!\n", nu);
	pthread_mutex_unlock(&simInfo->mtx_cout);
	lfork = nu;
	if (nu == 0)
		rfork = simInfo->_number_of_philosophers - 1;
	else
		rfork = nu - 1;
// {
	// pthread_mutex_lock(&simInfo->mtx_forks[lfork]);
	// philo_message(nu, "took left fork!\n", simInfo);
	// pthread_mutex_lock(&simInfo->mtx_forks[rfork]);
	// philo_message(nu, "took right fork!\n", simInfo);
	// philo_message(nu, "start eating!\n", simInfo);
	// ft_sleep(simInfo->_time_to_eat);
	// philo_message(nu, "start sleeping!\n", simInfo);
	// ft_sleep(simInfo->_time_to_sleep);
	// // if (gettime() - simInfo->simStartTime >= simInfo->_time_to_die)
	// // 	philo_message(nu, "dead! 💀\n", simInfo);
	// pthread_mutex_unlock(&simInfo->mtx_forks[lfork]);
	// pthread_mutex_unlock(&simInfo->mtx_forks[rfork]);}
	return NULL;
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
		while (i < simInfo._number_of_philosophers)
			if (pthread_create(&folks[i++], NULL, routine, (void *)&simInfo))
				exit_fatal("thread create error\n");
	}

	//ending party
	{
		// int i;
		
		// i = 0;
		// while (i < simInfo._number_of_philosophers)
		// 	if (pthread_mutex_destroy(&simInfo.mtx_forks[i++]))
		// 		exit_fatal("forks destroy error\n");
		// if (pthread_mutex_destroy(&simInfo.mtx_cout))
		// 	exit_fatal("cout destroy error\n");
		free(simInfo.mtx_forks);
		free(folks);
	}
	return (0);
}