#include "../srcs/philo_one.h"

int		ft_atoi(const char *s)
{
	int i;
	int minus;

	i = 0;
	minus = 1;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t' ||
			*s == '\v' || *s == '\f' || *s == '\r'))
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