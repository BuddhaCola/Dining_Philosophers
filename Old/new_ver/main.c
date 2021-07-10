#include <stdio.h>
#include <pthread.h>

typedef struct s_philo {
	int			counter;
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}				t_philo;

int		ft_atoi(const char *i);

t_philo	get_input(char *argv[])
{
	t_philo	simInfo;

	simInfo.counter = 0;		
	simInfo.number_of_philosophers = ft_atoi(argv[1]);
	simInfo.time_to_die = ft_atoi(argv[2]);
	simInfo.time_to_eat = ft_atoi(argv[3]);
	simInfo.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simInfo.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (simInfo);
}

int	main (int ac, char *av[])
{
	t_philo	simInfo;

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
	else
		simInfo = get_input(av);
	int i;
	pthread_t *threads = malloc(sizeof(pthread_t) * simInfo.number_of_philosophers);
	pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * simInfo.number_of_philosophers);
	pthread_mutex_t	print_mutex;
	
	i = 0;
	while (i < simInfo.number_of_philosophers)
	{
		pthread_create(threads, NULL, routine, simInfo);
	}
// 	printf("counter = %d\n\
// number_of_philosophers = %d\n\
// time_to_die = %d\n\
// time_to_eat = %d\n\
// time_to_sleep = %d\n\
// number_of_times_each_philosopher_must_eat = %d\n\
// ", simInfo.counter, simInfo.number_of_philosophers, simInfo.time_to_die, simInfo.time_to_eat, simInfo.time_to_sleep, simInfo.number_of_times_each_philosopher_must_eat);
	return (0);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	minus;

	i = 0;
	minus = 1;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'
			|| *s == '\v' || *s == '\f' || *s == '\r'))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			minus = -1;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		i *= 10;
		i += (*s++ - '0');
	}
	return (i * minus);
}
