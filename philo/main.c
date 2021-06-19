#include "philosophers.h"

static int	threading(t_info *information)
{
	int	i;

	i = 0;
	information->start_time = get_timems();
	if (pthread_create(&(information->check_death), NULL, death, information))
	{
		printf("Pthread create error!\n");
		return (0);
	}
	while (i < information->philo_num)
	{
		if (pthread_create(&(information->threads[i]), NULL,
				philo_actions, &(information->philosophers[i])))
		{
			printf("Pthread create error!\n");
			return (0);
		}
		i++;
	}
	if (pthread_join(information->check_death, NULL))
	{
		printf("Pthread join error!\n");
		return (0);
	}
	return (1);
}

static void	clean_exit(t_info *information)
{
	int	i;

	i = 0;
	while (i < information->philo_num)
	{
		pthread_detach(information->threads[i]);
		i++;
	}
	i = 0;
	while (i < information->philo_num)
	{
		pthread_mutex_destroy(&information->forks[i]);
		i++;
	}
	free(information->threads);
	free(information->forks);
	free(information->philosophers);
}

int	main(int argc, char **argv)
{
	t_info	information;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments, must be 4 or 5!\n");
		return (1);
	}
	else if (!check_args(argc, argv))
	{
		printf("Got some wrong data in arguments!\n");
		return (1);
	}
	else
	{
		if (!fill_info(&information, argv, argc))
		{
			printf("Got some wrong data in arguments!\n");
			return (1);
		}
		if (!init_mutex(&information) || !init_philos(&information)
			|| !threading(&information))
			return (1);
	}
	clean_exit(&information);
	return (0);
}
