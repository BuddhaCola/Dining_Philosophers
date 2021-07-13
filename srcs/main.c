#include "philo.h"

void	philo_message(int nu, char *str, t_philo *simInfo)
{
	pthread_mutex_lock(&simInfo->mtx_cout);
	printf("%04ld|philosopher %02d|%s\n",
		timeSinceStart(simInfo->simStartTime), nu, str);
	pthread_mutex_unlock(&simInfo->mtx_cout);
}

void	take_forks(t_philo *simInfo, int nu)
{
	if (nu % 2)
	{
		pthread_mutex_lock(&simInfo->mtx_forks[nu]);
		philo_message(nu, "took left fork", simInfo);
		pthread_mutex_lock(&simInfo->mtx_forks[nu - 1]);
		philo_message(nu, "took right fork", simInfo);
	}
	else
	{
		if (nu == 0)
			pthread_mutex_lock(&simInfo->mtx_forks
			[simInfo->_number_of_philosophers - 1]);
		else
			pthread_mutex_lock(&simInfo->mtx_forks[nu - 1]);
		philo_message(nu, "took right fork", simInfo);
		pthread_mutex_lock(&simInfo->mtx_forks[nu]);
		philo_message(nu, "took left fork", simInfo);

	}


	simInfo->report[nu] = timeSinceStart(simInfo->simStartTime)
			+ simInfo->_time_to_die;
	philo_message(nu, "eating", simInfo);
	ft_sleep(simInfo->_time_to_eat);


	if (nu % 2)
	{
		
			pthread_mutex_unlock(&simInfo->mtx_forks[nu - 1]);
		philo_message(nu, "put down right fork", simInfo);

		pthread_mutex_unlock(&simInfo->mtx_forks[nu]);
		philo_message(nu, "put down left fork", simInfo);
	}
	else
	{
		
		pthread_mutex_unlock(&simInfo->mtx_forks[nu]);
		philo_message(nu, "put down left fork", simInfo);
		if (nu == 0)
			pthread_mutex_unlock(&simInfo->mtx_forks
			[simInfo->_number_of_philosophers - 1]);
		else
			pthread_mutex_unlock(&simInfo->mtx_forks[nu - 1]);
		philo_message(nu, "put down right fork", simInfo);
	
	}
}

void	*dietcontrol(void *ptr)
{
	t_philo	*simInfo;
	int		i;
	int		fed;
	int		enough;

	simInfo = (t_philo *)ptr;
	enough = 0;
	fed = 0;
	ft_sleep(simInfo->_time_to_eat);
	while (!simInfo->endgame)
	{
		fed = simInfo->_number_of_philosophers;
		i = 0;
		while (i < simInfo->_number_of_philosophers)
		{
			if (simInfo->diet[i] < simInfo->_number_of_times_each_philosopher_must_eat)
				fed--;
			i++;
		}
		if (fed == simInfo->_number_of_philosophers)
		{	pthread_mutex_lock(&simInfo->mtx_cout);
			simInfo->endgame = 1;
			printf("that's all folks! fed = %d\n", fed);
			// pthread_mutex_unlock(&simInfo->mtx_cout);
			}
		}
	return (NULL);
}

void	*routine(void *ptr)
{
	t_philo	*simInfo;
	int		nu;

	simInfo = (t_philo *)ptr;
	nu = simInfo->counter++;
	while (!simInfo->endgame)
	{
		take_forks(simInfo, nu);
		
		// if (simInfo->_number_of_times_each_philosopher_must_eat)
		// 	simInfo->diet[nu]++;
		// ft_sleep(simInfo->_time_to_eat);
		// pthread_mutex_unlock(&simInfo->mtx_forks[nu]);
		// if (nu == 0)
		// 	pthread_mutex_unlock(&simInfo->mtx_forks
		// 	[simInfo->_number_of_philosophers - 1]);
		// else
		// 	pthread_mutex_unlock(&simInfo->mtx_forks[nu - 1]);
		philo_message(nu, "fell asleep", simInfo);
		ft_sleep(simInfo->_time_to_sleep);
		philo_message(nu, "thinking", simInfo);
	}
	return (NULL);
}

void	ending_party(t_philo *simInfo, pthread_t *folks)
{
	int	i;

	// philo_message(666, "ending!\n", simInfo);

	i = 0;
	while (i < simInfo->_number_of_philosophers)
	{
		// pthread_join(folks[i], NULL);
		pthread_mutex_destroy(&simInfo->mtx_forks[i++]);
	}
	pthread_mutex_destroy(&simInfo->mtx_cout);
	free(simInfo->mtx_forks);
	free(folks);
	free(simInfo->report);
	if (simInfo->_number_of_times_each_philosopher_must_eat)
		free(simInfo->diet);
}

void	the_feast(t_philo *simInfo)
{
	int	i;
	// pthread_t	*dietcontrol_thread = malloc(sizeof(pthread_t *));

	ft_sleep(simInfo->_time_to_eat * 2);
	// if (simInfo->_number_of_times_each_philosopher_must_eat)
	// 	pthread_create(dietcontrol_thread, NULL, dietcontrol, simInfo);
	while (!simInfo->endgame)
	{
		i = 0;
		while (i < simInfo->_number_of_philosophers)
		{
			if (timeSinceStart(simInfo->simStartTime)
				- simInfo->report[i] >= simInfo->_time_to_die)
			{
				{
					pthread_mutex_lock(&simInfo->mtx_cout);
					simInfo->endgame = 1;
					printf("%04ld|philosopher %02d|DEAD!\n",
						timeSinceStart(simInfo->simStartTime), i + 1);
				}
				ending_party(simInfo, simInfo->philos);
				break ;
			}
			i++;
		}
	}
	// pthread_join(*dietcontrol_thread, NULL);
}

int	main(int ac, char **av)
{
	t_philo		simInfo;
	int			i;

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
	i = 0;
	while (i < simInfo._number_of_philosophers)
		if (pthread_create(&simInfo.philos[i++],
				NULL, routine, (void *)&simInfo))
			exit_fatal("thread create error\n");
	the_feast(&simInfo);
	return (0);
}
