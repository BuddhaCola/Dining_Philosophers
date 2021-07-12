#ifndef PHILO_H
#define PHILO_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#include <stdio.h> //убрать!

typedef struct	s_philo {
	int				_number_of_philosophers;
	int				_time_to_die;
	int				_time_to_eat;
	int				_time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				counter;
	long			simStartTime;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_cout;
	long			*report;
	int				endgame;
}				t_philo;

int		ft_atoi(const char *i);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstr(char *str);
char	*ft_itoa(int n);

void	exit_fatal();
long	gettime();
void	ft_sleep(int msec);
t_philo	get_input(char *argv[]);
long	timeSinceStart(long start);

#endif // !PHILO_H