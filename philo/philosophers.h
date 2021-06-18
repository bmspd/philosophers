#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
typedef pthread_mutex_t t_mutex;
struct s_info;

typedef struct s_philo
{
	int	id;
	unsigned left_fork;
	unsigned right_fork;
	struct s_info *information;
	uint64_t starve_start;
	int eat_times;
}t_philo;

typedef struct s_info {
	int philo_num;
	uint64_t start_time;
	uint64_t die_time;
	u_int64_t eat_time;
	uint64_t sleep_time;
	int meal_number;
	int meal_counter;
	t_mutex print;
	t_mutex *forks;
	t_philo *philosophers;
	pthread_t *threads;
	pthread_t check_death;
	int died;
}t_info;
int	ft_atoi(const char *str);
int	check_args(int argc, char **argv);
#endif
