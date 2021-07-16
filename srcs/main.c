#include "philo.h"

void	philo_message(int nu, char *str, t_philo *simInfo)
{
	if (simInfo->endgame)
		return ;
	pthread_mutex_lock(&simInfo->mtx_cout);
	if (!simInfo->endgame)
		printf("%04ld|philosopher %02d|%s\n", timeSinceStart(simInfo->simStartTime), nu, str);
	pthread_mutex_unlock(&simInfo->mtx_cout);
}

int		philo_sleep(t_philo *simInfo, long toWait)
{
	ft_sleep(toWait);
	if (simInfo->endgame)
		return (1);
	return(0);
}

void	whatTheFork(t_philo *simInfo, int nu, int (*fun)(pthread_mutex_t *))
{
	fun(&simInfo->mtx_forks[nu]);
	if (fun != pthread_mutex_lock)
		philo_message(nu, "took left fork", simInfo);
	if (nu == simInfo->_number_of_philosophers)
		fun(&simInfo->mtx_forks[0]);
	else
		fun(&simInfo->mtx_forks[nu + 1]);
	if (fun != pthread_mutex_lock)
		philo_message(nu, "took right fork", simInfo);
}

int	sufferLoop(t_philo *simInfo, int nu, int fed[2])
{
	whatTheFork(simInfo, nu, &pthread_mutex_lock);
	pthread_mutex_lock(&simInfo->mtx_status);
	if (simInfo->endgame)
		return (1);
	if (!simInfo->endgame)
		simInfo->report[nu - 1] = timeSinceStart(simInfo->simStartTime);
	pthread_mutex_unlock(&simInfo->mtx_status);
	philo_message(nu, "eat", simInfo);
	if (simInfo->diet)
	{
		pthread_mutex_lock(&simInfo->mtx_status);
		if (!fed[1])
		{
			philo_message(nu, "updated his diet", simInfo);
			fed[0]++;
			if (fed[0] >= simInfo->_number_of_times_each_philosopher_must_eat)
			{
				fed[1] = 1;
				philo_message(nu, "fed_up!", simInfo);
				simInfo->fed++;
				// return (1);
			}
		}
		pthread_mutex_unlock(&simInfo->mtx_status);
	}
	if (philo_sleep(simInfo, simInfo->_time_to_eat))
		return (1);
	whatTheFork(simInfo, nu, &pthread_mutex_unlock);
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
	pthread_mutex_lock(&simInfo->mtx_status);
	nu = simInfo->counter++ + 1;
	pthread_mutex_unlock(&simInfo->mtx_status);
	if (nu % 2)
		if (philo_sleep(simInfo, simInfo->_time_to_eat))
			return (NULL);
	while (!simInfo->endgame)
		if (sufferLoop(simInfo, nu, fed))
			break ;
	return (NULL);
}

void	ending_party(t_philo *simInfo)
{
	int	i;

	i = 0;
	while (i < simInfo->_number_of_philosophers)
	{
		pthread_detach(simInfo->philos[i]);
		pthread_mutex_destroy(&simInfo->mtx_forks[i++]);
	}
	pthread_mutex_destroy(&simInfo->mtx_cout);
	pthread_mutex_destroy(&simInfo->mtx_status);
	free(simInfo->mtx_forks);
	free(simInfo->report);
	free(simInfo->philos);
	if (simInfo->_number_of_times_each_philosopher_must_eat)
		free(simInfo->diet);
}

int	dietControl(t_philo *simInfo)
{
	int i;
	int	fed;

	i = 0;
	fed = 0;
	while (i < simInfo->_number_of_philosophers)
	{
		// pthread_mutex_lock(&simInfo->mtx_status);
		if (simInfo->diet[i] >= simInfo->_number_of_times_each_philosopher_must_eat)
			fed++;
		// pthread_mutex_unlock(&simInfo->mtx_status);
	}
	pthread_mutex_lock(&simInfo->mtx_cout);
	printf("dietcontrol: fed %d\n", fed);
	pthread_mutex_unlock(&simInfo->mtx_cout);
	// if (fed >= simInfo->_number_of_philosophers)
		return (1);
	// return (0);	
}

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
					pthread_mutex_lock(&simInfo->mtx_status);
					pthread_mutex_lock(&simInfo->mtx_cout);
					simInfo->endgame = 1;
					printf("%04ld|philosopher %02d|is DEAD! (last meal %ld)\n", timeSinceStart(simInfo->simStartTime), i + 1, simInfo->report[i]);
					ft_sleep(simInfo->_time_to_die);
					// pthread_mutex_unlock(&simInfo->mtx_status);
					// pthread_mutex_unlock(&simInfo->mtx_cout);
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
			pthread_mutex_lock(&simInfo->mtx_status);
			pthread_mutex_lock(&simInfo->mtx_cout);
			simInfo->endgame = 1;
			printf("%04ld|that's all folks!\n", timeSinceStart(simInfo->simStartTime));
			ft_sleep(simInfo->_time_to_die);
			return NULL;
		}
	}
	return NULL;
}

int	main(int ac, char **av)
{
	t_philo		simInfo;
	int			i;
	pthread_t	*monitor_t = malloc(sizeof(pthread_t));
	pthread_t	*diet_monitor_t = malloc(sizeof(pthread_t));

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
	{
		simInfo.report[i] = 0;
		if (simInfo.diet)
			simInfo.diet[i] = 0;
		if (pthread_create(&simInfo.philos[i], NULL, routine, (void *)&simInfo))
			exit_fatal("thread create error\n");
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
