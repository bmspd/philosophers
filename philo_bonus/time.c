#include "philosophers.h"

uint64_t	get_timems(void)
{
	struct timeval	current_time;
	uint64_t		current_time_ms;

	gettimeofday(&current_time, NULL);
	current_time_ms = (current_time.tv_sec * 1000000
			+ current_time.tv_usec) / 1000;
	return (current_time_ms);
}

void	smart_sleep(uint64_t time)
{
	uint64_t	t;

	t = get_timems();
	while (get_timems() - t < time)
	{
		usleep(50);
	}
}
