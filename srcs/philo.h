#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	int				_number_of_philosophers;
	int				_time_to_die;
	int				_time_to_eat;
	int				_time_to_sleep;
	int				_number_of_times_each_philosopher_must_eat;
	int				counter;
	pthread_t		*philos;
	long			simStartTime;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_cout;
	long			*report;
	int				*diet;
	int				fed;
	int				endgame;
}				t_philo;

int		ft_atoi(const char *i);
int		ft_strlen(char *str);
void	ft_putstr_fd(char *str, int fd);
void	ft_putstr(char *str);
char	*ft_itoa(int n);

void	exit_fatal(void);
long	gettime(void);
void	ft_sleep(int msec);

void	philo_message(int nu, char *str, t_philo *simInfo);
int		philo_sleep(t_philo *simInfo, long toWait);
int		get_input(int ac, char *argv[], t_philo *simInfo);
int		threads_creation(t_philo *simInfo);
long	timeSinceStart(long start);
void	set_stage(t_philo *simInfo);
void	*routine(void *ptr);
void	whatTheFork(t_philo *simInfo, int nu, int (*fun)(pthread_mutex_t *));
int		sufferLoop(t_philo *simInfo, int nu, int fed[2]);
void	*routine(void *ptr);
void	*monitor(void *ptr);
void	*diet_monitor(void *ptr);

#endif