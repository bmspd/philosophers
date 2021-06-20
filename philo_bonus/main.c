#include "philosophers.h"

void	clean_exit(t_info *information)
{
	int	i;

	i = 0;
	waitpid(-1, 0, 0);
	while (i < information->philo_num)
	{
		kill(information->philosophers[i].pid, 15);
		i++;
	}
	sem_close(information->forks);
	sem_close(information->print);
	sem_unlink("/forks");
	sem_unlink("/print");
}

static void	making_forks(t_info *information)
{
	int	i;

	i = 0;
	init_sema(information);
	information->start_time = get_timems();
	while (i < information->philo_num)
	{
		information->philosophers[i].pid = fork();
		if (information->philosophers[i].pid == 0)
		{
			philosopher(&information->philosophers[i]);
		}
		usleep(100);
		i++;
	}
	clean_exit(information);
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
		if (!init_philos(&information))
			return (1);
	}
	making_forks(&information);
	return (0);
}
