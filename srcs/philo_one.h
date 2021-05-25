#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>


#define SLEEP		0
#define EAT			1
#define THINKING	2
#define DEAD		3


typedef struct	s_input
{
	int			philo_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			fifth_argument;
}				t_input;

typedef	struct	s_philosopher
{
	pthread_t		philothread;
	int				position;
	t_input			*manifest;
	long int		*watches;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}				t_philosopher;

typedef struct	s_philo
{
	t_input			inputdata;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	long int		start_time;
}	t_philo;

int		ft_atoi(const char *s);

#endif