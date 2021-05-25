#include "philo_one.h"
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || !fd)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
	ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || !fd)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

char	*ft_strchr(const char *s, int n)
{
	if (*s != '\0' && *s != (char)n)
	{
		while (*++s)
		{
			if (*s == (char) n)
				return ((char *) s);
		}
	}
	if (*s == (char)n)
		return ((char *)s);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
	{
		i++;
	}
	return (i);
}

int    ft_checkforbiddensymbols(char **args)
{
	char	*str;

	while (*args)
	{
		str = *args;
		while(*str)
		{
			if (ft_isdigit(*str) || ft_strchr("-+ ", *str))
				(str)++;
			else
			{
				ft_putstr_fd("wrong symbol: ", 2);
				ft_putendl_fd(str, 2);
				return (1);
			}
		}
		(args)++;
	}
	return (0);
}

long int gettime()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec);
}

void	*routine(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	pthread_mutex_lock(philosopher->lfork);
//	printf("⌚️|%ld| 👳%02d🥄👈\n", *philosopher->watches - gettime(), philosopher->position + 1);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_lock(philosopher->rfork);
//	printf("⌚️|%ld| 👳%02d👉🥄\n", *philosopher->watches - gettime(), philosopher->position + 1);
	pthread_mutex_unlock(philosopher->rfork);
	printf("⌚️|%ld| 👳%02d👐\n", gettime() - *philosopher->watches, philosopher->position + 1);
	return (NULL);
}

int		main (int argc, char **argv)
{
	t_philo		all;

	if (argc < 5 || argc > 6)
		printf("1wrong arguments!\n");
	else if (ft_checkforbiddensymbols(&argv[1]))
		printf("2wrong arguments!\n");
	else {
		all.inputdata.philo_num = ft_atoi(argv[1]);
		all.inputdata.time_to_die = ft_atoi(argv[2]);
		all.inputdata.time_to_eat = ft_atoi(argv[3]);
		all.inputdata.time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			all.inputdata.fifth_argument = ft_atoi(argv[5]);
		{
			int i;

			all.forks = malloc(sizeof(pthread_mutex_t) * all.inputdata.philo_num);
			if (!all.forks)
				return (-1);
			i = 0;
			while (i < all.inputdata.philo_num)
			{
				pthread_mutex_init(&all.forks[i], NULL);
				i++;
			}
		}
		{

			all.start_time = gettime();
			printf("time is |%ld|", all.start_time);
			{
				int i;

				all.philosophers = malloc(
						sizeof(t_philosopher) * all.inputdata.philo_num);
				i = 0;
				while (i < all.inputdata.philo_num)
				{
					all.philosophers[i].position = i;
					all.philosophers[i].manifest = &all.inputdata;
					all.philosophers[i].rfork = &all.forks[i];
					if (i == 0)
						all.philosophers[i].lfork = &all.forks[all.inputdata.philo_num];
					else
						all.philosophers[i].lfork = &all.forks[i - 1];
					all.philosophers[i].watches = &all.start_time;
					pthread_create(&all.philosophers[i].philothread, NULL,
								   &routine, (void *) &all.philosophers[i]);
					i++;
				}
			}
		}

		while (1) {
		}
	}

	printf("exiting!\n");
	return (0);
}