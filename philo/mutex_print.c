#include "philosophers.h"

static void	eating_part(t_philo *philosopher, char flag, uint64_t current_time)
{
	t_info		*information;
	uint64_t	diff;

	information = philosopher->information;
	diff = current_time - information->start_time;
	printf("%lld %d is eating\n", diff, philosopher->id);
	if (information->meal_number != -1)
	{
		philosopher->eat_times += 1;
		if (philosopher->eat_times == information->meal_number)
			information->meal_counter += 1;
	}
}

void	mutex_print(t_philo *philosopher, char flag, uint64_t current_time)
{
	t_info		*information;
	uint64_t	diff;

	information = philosopher->information;
	pthread_mutex_lock(&(information->print));
	diff = current_time - information->start_time;
	if (flag == 'f')
		printf("%lld %d has taken a fork\n", diff, philosopher->id);
	else if (flag == 'e')
		eating_part(philosopher, flag, current_time);
	else if (flag == 's')
		printf("%lld %d is sleeping\n", diff, philosopher->id);
	else if (flag == 't')
		printf("%lld %d is thinking\n", diff, philosopher->id);
	else if (flag == 'd')
	{
		printf("%lld %d died\n", diff, philosopher->id);
		return ;
	}
	pthread_mutex_unlock(&(information->print));
}
