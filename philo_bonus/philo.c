#include "philosophers.h"

void	*death(void *philosopher)
{
	t_info	*info;
	t_philo	*philo;

	philo = philosopher;
	info = philo->information;
	while (1)
	{
		if (get_timems() - philo->starve_start > info->die_time)
		{
			sema_print(info->philosophers, 'd', get_timems());
			philo->rip = 1;
			exit(1);
		}
		usleep(100);
	}
	return (0);
}

static void	eating(t_info *information, t_philo *philo)
{
	sem_wait(information->forks);
	sema_print((void *)philo, 'f', get_timems());
	sem_wait(information->forks);
	sema_print((void *)philo, 'f', get_timems());
	sema_print((void *)philo, 'e', get_timems());
	philo->starve_start = get_timems();
	smart_sleep(information->eat_time);
	sem_post(information->forks);
	sem_post(information->forks);
}

void	philosopher(t_philo *philosopher)
{
	t_philo	*philo;
	t_info	*information;

	philo = (t_philo *)philosopher;
	information = philo->information;
	philo->starve_start = get_timems();
	pthread_create(&philosopher->check_death, NULL, death, philosopher);
	while (!philosopher->rip)
	{
		eating(information, philosopher);
		sema_print(philosopher, 's', get_timems());
		smart_sleep(information->sleep_time);
		sema_print(philosopher, 't', get_timems());
	}
	pthread_join(philosopher->check_death, NULL);
}
