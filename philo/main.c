#include "philosophers.h"

void init_mutex(t_info *information)
{
	int i;

	i = 0;
	information->forks = malloc(sizeof(t_mutex) * information->philo_num);
	while (i < information->philo_num)
	{
		pthread_mutex_init(&(information->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(information->print), NULL);
}

void init_philos(t_info *information)
{
	int i;

	i = 0;

	information->philosophers = malloc(sizeof(t_philo) * information->philo_num);
	information->threads = malloc(sizeof(pthread_t) * information->philo_num);
	while (i < information->philo_num)
	{
		information->philosophers[i].id = i + 1;
		information->philosophers[i].right_fork = i;
		if (i == 0)
			information->philosophers[i].left_fork = information->philo_num - 1;
		else
			information->philosophers[i].left_fork = i - 1;
		information->philosophers[i].information = information;
		information->philosophers[i].starve_start = -1;
		information->philosophers[i].eat_times = 0;
		i++;
	}
}

void fill_info(t_info *information, char **argv, int argc)
{

	information->philo_num = ft_atoi(argv[1]);
	information->die_time = ft_atoi(argv[2]);
	information->eat_time = ft_atoi(argv[3]);
	information->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		information->meal_number = ft_atoi(argv[5]);
	else
		information->meal_number = -1;
	information->meal_counter = 0;
}

uint64_t get_timems(void)
{
	struct timeval current_time;
	uint64_t current_time_ms;

	gettimeofday(&current_time, NULL);
	current_time_ms = (current_time.tv_sec * 1000000 + current_time.tv_usec) / 1000;
	return (current_time_ms);
}

void	smart_sleep(uint64_t time)
{
	uint64_t	t;

	t = get_timems();
	while (get_timems() - t < time)
	{
		usleep(1);
	}
}
void *death(void *information);
void mutex_print(t_philo *philosopher, char flag, uint64_t current_time)
{
	t_info *information;
	information = philosopher->information;

	pthread_mutex_lock(&(information->print));
	uint64_t diff = current_time - information->start_time;
	if (flag == 'f')
		printf("%lld %d has taken a fork\n",diff, philosopher->id);
	else if (flag == 'e')
	{
		printf("%lld %d is eating\n",diff, philosopher->id);
	}
	else if (flag == 's')
	{
		if (information->meal_number != -1)
		{
			philosopher->eat_times += 1;
			if (philosopher->eat_times == information->meal_number)
			{
				information->meal_counter += 1;
				//pthread_detach(information->threads[philosopher->id - 1]);
			}
		}
		printf("%lld %d is sleeping\n", diff, philosopher->id);
	}
	else if (flag == 't')
		printf("%lld %d is thinking\n", diff, philosopher->id);
	else if (flag == 'd')
	{
		printf("%lld %d died\n", diff, philosopher->id);
		int i = 0;
		while (i < information->philo_num)
		{
			i++;
		}
		return ;
	}
	else if (flag == 'z')
	{

		free(information->threads);
	}

	pthread_mutex_unlock(&(information->print));
}

void *philo_actions(void *philosopher)
{
	int i;
	t_philo *philo;
	t_info *information;
	philo = (t_philo *)philosopher;
	information = philo->information;
	if (philo->id % 2)
		usleep(1500);
	philo->starve_start = get_timems();
	while (1)
	{
		pthread_mutex_lock(&(information->forks[philo->left_fork]));
		mutex_print(philosopher, 'f', get_timems());
		pthread_mutex_lock(&(information->forks[philo->right_fork]));
		mutex_print(philosopher, 'f', get_timems());
		mutex_print(philosopher, 'e', get_timems());
		smart_sleep(information->eat_time);
		philo->starve_start = get_timems();
		pthread_mutex_unlock(&(information->forks[philo->left_fork]));
		pthread_mutex_unlock(&(information->forks[philo->right_fork]));
		mutex_print(philosopher, 's',get_timems());
		if (philo->eat_times == information->meal_number)
		{
			philo->starve_start = -1;
			break;
		}
		smart_sleep(information->sleep_time);
		mutex_print(philosopher, 't', get_timems());

	}
	return (NULL);
}

void *death(void *information)
{
	if (information == NULL)
		return (0);
	int j;
	int i;
	t_info *info = (t_info *) information;
	while(1)
	{
		i = 0;
		j = 0;
		while (i < info->philo_num)
		{
			if (get_timems() - info->philosophers[i].starve_start > info->die_time
				&& info->philosophers[i].starve_start != -1)
			{
				mutex_print(&info->philosophers[i], 'd', get_timems());
				return 0;
			}
			if (info->meal_counter == info->philo_num)
			{
				return 0;
			}
			usleep(100);
			i++;
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		printf("Wrong number of arguments, must be 4 or 5!\n");
	else if (!check_args(argc, argv))
		printf("Got some wrong data in arguments!\n");
	else
	{
		t_info information;
		fill_info(&information, argv, argc);
		init_mutex(&information);
		init_philos(&information);
		int i = 0;
		pthread_create(&(information.check_death), NULL, death, &information);
		information.start_time = get_timems();
		while (i < information.philo_num)
		{
			pthread_create(&(information.threads[i]), NULL, philo_actions, &(information.philosophers[i]));
			i++;
		}
		pthread_join(information.check_death, NULL);
	}
	return(0);
}
