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

void	ft_sleep(int tosleep)
{
	int	i;

	tosleep *= 1000;
	i = tosleep / 60;
	while (i)
	{
		usleep(60);
		i--;
	}
	usleep(tosleep % 60);
}

long int gettime()
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*routine(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	philosopher->alive = 1;
	printf("👳%d\n", philosopher->position);
	printf("*👈%p\n", philosopher->lfork);
	printf("*👉%p\n", philosopher->rfork);
	while (philosopher->alive)
	{
		philosopher->last_meal = *philosopher->watches;
//		pthread_mutex_lock(philosopher->lfork);
//		pthread_mutex_unlock(philosopher->lfork);
//		pthread_mutex_lock(philosopher->rfork);
		usleep(philosopher->manifest->time_to_eat * 1000);
		printf("🤔|%02d|поел!		|⌚️%ld|\n", philosopher->position,
			   gettime() - *philosopher->watches);
		{
			pthread_mutex_unlock(philosopher->lfork);
			printf("%d|%s\n", philosopher->position, "Put left fork down");
		}
		{
			pthread_mutex_unlock(philosopher->rfork);
			printf("%d|%s\n", philosopher->position, "Put right fork down");
		}
		usleep(philosopher->manifest->time_to_sleep * 1000);
	}
	return (NULL);
}

t_philo	get_input(char **argv)
{
	t_philo	all;
	all.inputdata.philo_num = ft_atoi(argv[1]);
	all.inputdata.time_to_die = ft_atoi(argv[2]);
	all.inputdata.time_to_eat = ft_atoi(argv[3]);
	all.inputdata.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all.inputdata.fifth_argument = ft_atoi(argv[5]);
	return (all);
}

int	serve_forks(t_philo *all)
{
	int i;

	all->forks = malloc(sizeof(pthread_mutex_t) * all->inputdata.philo_num);
	if (!all->forks)
		return (-1);
	i = 0;
	while (i < all->inputdata.philo_num)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		i++;
	}
	return (0);
}

void	sit_down_and_eat(t_philo *all)
{
	pthread_mutex_init(&all->print_mutex, NULL);
	all->philosophers = malloc(sizeof(t_philosopher) * all->inputdata.philo_num);
	{
		int i;
//
		i = 0;
		while (i < all->inputdata.philo_num)
		{
			all->philosophers[i].position = i + 1;
			all->philosophers[i].manifest = &all->inputdata;
			if (i == 0)
			{
				all->philosophers[i].rfork = &(all->forks[
						all->inputdata.philo_num - 1]);
				printf("%d👉%p\n", i, all->philosophers[i].rfork);
			}
			else
				all->philosophers[i].rfork = &all->forks[i - 1];
			all->philosophers[i].lfork = &all->forks[i];
			all->philosophers[i].watches = &all->start_time;
//			//start!
			i++;
		}
		i = 0;
		while (i < all->inputdata.philo_num)
		{
			pthread_create(&all->philosophers[i].philothread, NULL,
						   &routine, (void *) &all->philosophers[i]);
			i++;
		}
	}
}

void	destroy_forks(t_philo *all)
{
	int i;

	i = 0;
	while (i < all->inputdata.philo_num)
	{
	pthread_mutex_destroy(&all->forks[i]);
	i++;
	}
}

int	dinnertime(char **argv)
{
	t_philo		all;

	all = get_input(argv);
	//добавить проверку на ошибки!
	if (serve_forks(&all))
		return (-1);
	all.start_time = gettime();
	printf("time is |%ld|\n", all.start_time);
	sit_down_and_eat(&all);
	pthread_mutex_destroy(&all.print_mutex);
	destroy_forks(&all);
	while (1) {
	}
}

int		main (int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		printf("1wrong arguments!\n");
	else if (ft_checkforbiddensymbols(&argv[1]))
		printf("2wrong arguments!\n");
	else
		return (dinnertime(argv));
	return (0);
}