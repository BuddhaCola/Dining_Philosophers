# include "philo.h"

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

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

void	exit_fatal(char *str)
{
	ft_putstr_fd(str, 2);
	exit(-1);
}

//itoa
static int	ft_digits(int n)
{
	int				i;
	unsigned int	nu;

	i = 0;
	if (n < 0)
	{
		nu = ((unsigned int)(n * -1));
		i++;
	}
	else
		nu = (unsigned int)n;
	while (nu >= 10)
	{
		nu /= 10;
		i++;
	}
	return (i + 1);
}

char		*ft_itoa(int n)
{
	char			*asc;
	int				len;
	unsigned int	nu;

	len = ft_digits(n);
	asc = malloc(sizeof(char) * len + 1);
	if (!(asc))
		return (NULL);
	memset(asc, 0, len + 1);
	if (n < 0)
	{
		*asc = '-';
		nu = ((unsigned int)(n * -1));
	}
	else
		nu = (unsigned int)n;
	len--;
	while (nu >= 10)
	{
		*(asc + len) = nu % 10 + '0';
		nu /= 10;
		len--;
	}
	*(asc + len) = nu % 10 + '0';
	return (asc);
}