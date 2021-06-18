#include "philosophers.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

static int check_string(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc == 5)
	{
		if(!check_string(argv[1]) || !check_string(argv[2])
		  ||!check_string(argv[3]) || !(check_string(argv[4])))
			return (0);
	}
	else if (argc == 6)
	{
		if(!check_string(argv[1]) || !check_string(argv[2])
		   ||!check_string(argv[3]) || !(check_string(argv[4]))
		   ||!check_string(argv[5]))
			return (0);
	}
	return (1);
}