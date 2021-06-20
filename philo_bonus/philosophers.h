#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				id;
	unsigned int	left_fork;
	unsigned int	right_fork;
	struct s_info	*information;
	uint64_t		starve_start;
	int				eat_times;
	int				pid;
	pthread_t		check_death;
	int				rip;
}					t_philo;

typedef struct s_info {
	int			philo_num;
	uint64_t	start_time;
	uint64_t	die_time;
	u_int64_t	eat_time;
	uint64_t	sleep_time;
	int			meal_number;
	int			meal_counter;
	sem_t		*forks;
	sem_t		*print;
	t_philo		*philosophers;
}				t_info;

uint64_t	ft_atoi(const char *str);
int			check_args(int argc, char **argv);

int			init_sema(t_info *information);
int			init_philos(t_info *information);
int			fill_info(t_info *information, char **argv, int argc);

void		philosopher(t_philo *philosopher);
void		*death(void *information);
void		sema_print(t_philo *philosopher, char flag, uint64_t current_time);

uint64_t	get_timems(void);
void		smart_sleep(uint64_t time);
#endif
