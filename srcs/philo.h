#ifndef PHILO_H
#define PHILO_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_philo {
	int				counter;
	long			simStartTime;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_cout;
	int				_number_of_philosophers;
	int				_time_to_die;
	int				_time_to_eat;
	int				_time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
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


#endif // !PHILO_H