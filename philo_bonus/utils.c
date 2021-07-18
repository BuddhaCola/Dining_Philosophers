#include "philo.h"

long	timeSinceStart(long start)
{
	return (gettime() - start);
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	exit_fatal(char *str)
{
	ft_putstr_fd(str, 2);
	return (-1);
}
