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

void	*routine(void *args)
{
	t_philo		*all;

//	all->lfork =
	all = (t_philo *)args;
	usleep(all->time_to_eat);
	return (NULL);
}

int		main (int argc, char **argv)
{
	pthread_t	*👴;
	t_philo		all;

	if (argc < 5 || argc > 6 || ft_checkforbiddensymbols(&argv[1]))
		printf("wrong arguments!\n");
	else
	{
		all.philo_num = ft_atoi(argv[1]);
		all.time_to_die = ft_atoi(argv[2]);
		all.time_to_eat = ft_atoi(argv[3]);
		all.time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			all.fifth_argument = ft_atoi(argv[5]);
		👴 = malloc(sizeof(pthread_t *) * all.philo_num + 1);
		👴[all.philo_num] = NULL;

		all.forks = malloc(sizeof(pthread_mutex_t *) * all.philo_num - 1);

		int i;
		i = 0;
		while (i < all.philo_num - 1)
		{
			pthread_mutex_init(&all.forks[i], NULL);
			i++;
		}

		i = 0;
		while (i < all.philo_num)
		{
			pthread_create(&👴[i], NULL, &routine, (void *)&all);
			pthread_join(👴[i], NULL);
			i++;
		}

		i = 0;
		while (i < all.philo_num - 1)
		{
			pthread_mutex_destroy(&all.forks[i]);
			i++;
		}
	}
	if (all.forks)
		free(all.forks);
	return (0);
}