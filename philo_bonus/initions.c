#include "philosophers.h"
int	init_sema(t_info *information)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	information->forks = sem_open("/forks", O_CREAT, S_IRWXU,
			information->philo_num);
	information->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	info->philosophers = malloc(sizeof(t_philo) * info->philo_num);
	if (!info->philosophers)
	{
		printf("Malloc error!\n");
		return (0);
	}
	while (i < info->philo_num)
	{
		info->philosophers[i].id = i + 1;
		info->philosophers[i].right_fork = i;
		if (i == 0)
			info->philosophers[i].left_fork = info->philo_num - 1;
		else
			info->philosophers[i].left_fork = i - 1;
		info->philosophers[i].information = info;
		info->philosophers[i].starve_start = -1;
		info->philosophers[i].eat_times = 0;
		info->philosophers[i].rip = 0;
		i++;
	}
	return (1);
}

int	fill_info(t_info *information, char **argv, int argc)
{
	information->philo_num = (int)ft_atoi(argv[1]);
	information->die_time = ft_atoi(argv[2]);
	information->eat_time = ft_atoi(argv[3]);
	information->sleep_time = ft_atoi(argv[4]);
	if (information->philo_num < 1 || information->philo_num > 200
		|| information->die_time < 1 || information->die_time > INT64_MAX
		|| information->eat_time < 1 || information->eat_time > INT64_MAX
		|| information->sleep_time < 1 || information->sleep_time > INT64_MAX)
		return (0);
	if (argc == 6)
	{
		information->meal_number = (int) ft_atoi(argv[5]);
		if (information->meal_number < 1
			|| information->meal_number > INT32_MAX)
			return (0);
	}
	else
		information->meal_number = -1;
	information->meal_counter = 0;
	return (1);
}
