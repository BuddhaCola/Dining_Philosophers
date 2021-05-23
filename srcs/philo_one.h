#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_philosopher
{
	int				position;
	int				lfork;
	int				rfork;
}				t_philosopher;

typedef struct	s_philo
{
	int					philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					fifth_argument;
	pthread_mutex_t 	*forks;
}				t_philo;


int		ft_atoi(const char *s);

#endif