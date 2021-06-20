#include "philosophers.h"

static void	eating(t_info *information, t_philo *philo)
{
	pthread_mutex_lock(&(information->forks[philo->left_fork]));
	mutex_print((void *)philo, 'f', get_timems());
	pthread_mutex_lock(&(information->forks[philo->right_fork]));
	mutex_print((void *)philo, 'f', get_timems());
	mutex_print((void *)philo, 'e', get_timems());
	philo->starve_start = get_timems();
	smart_sleep(information->eat_time);
	pthread_mutex_unlock(&(information->forks[philo->left_fork]));
	pthread_mutex_unlock(&(information->forks[philo->right_fork]));
}

void	*philo_actions(void *philosopher)
{
	t_philo	*philo;
	t_info	*information;

	philo = (t_philo *)philosopher;
	information = philo->information;
	if (philo->id % 2)
		usleep(1500);
	philo->starve_start = get_timems();
	while (1)
	{
		eating(information, philosopher);
		mutex_print(philosopher, 's', get_timems());
		if (philo->eat_times == information->meal_number)
		{
			philo->starve_start = -1;
			break ;
		}
		smart_sleep(information->sleep_time);
		mutex_print(philosopher, 't', get_timems());
	}
	return (NULL);
}

void	*death(void *information)
{
	int		i;
	t_info	*info;

	info = (t_info *) information;
	while (1)
	{
		i = 0;
		while (i < info->philo_num)
		{
			if (get_timems() - info->philosophers[i].starve_start
				> info->die_time
				&& (int) info->philosophers[i].starve_start != -1)
			{
				mutex_print(&info->philosophers[i], 'd', get_timems());
				return (0);
			}
			if (info->meal_counter == info->philo_num)
			{
				return (0);
			}
			usleep(100);
			i++;
		}
	}
	return (0);
}
