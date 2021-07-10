#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

#include <stdio.h>

typedef struct s_philo {
	int			counter;
	long		simStartTime;
	int			_number_of_philosophers;
	int			_time_to_die;
	int			_time_to_eat;
	int			_time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
}		t_philo;

long	gettime() {
	struct timeval	time;
	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

void	ft_sleep(int msec) {
	long	waketime;

	waketime = gettime() + msec;
	while (1) {
		if (gettime() >= waketime)
			return;
	}
}

int		ft_atoi(const char *i);

t_philo	get_input(char *argv[])
{
	t_philo	simInfo;

	simInfo.counter = 0;
	simInfo.simStartTime = gettime();
	simInfo._number_of_philosophers = ft_atoi(argv[1]);
	simInfo._time_to_die = ft_atoi(argv[2]);
	simInfo._time_to_eat = ft_atoi(argv[3]);
	simInfo._time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		simInfo.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (simInfo);
}

int main (int ac, char **av)
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
	simInfo = get_input(av);
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


// 164000 rub 