#include "minitalk.h"

static int	ft_atoi (const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return (res * sign);
}

static void	*ft_memset (void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

static void	ft_empty(__attribute__((unused))int signum, __attribute__((unused))
	siginfo_t *info_list, __attribute__((unused)) void *no_name)
{
}

static void	converter (int pid, char *str)
{
	static int	i;
	char		c;

	while (*str)
	{
		c = *str;
		i = 128;
		while (i >= 1)
		{
			usleep(30);
			if (i & c)
			{
				if (kill(pid, SIGUSR1) == -1)
					write(1, "ERROR PID\n", 10);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					write(1, "ERROR PID\n", 10);
			}
			i /= 2;
			pause ();
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act_client;
	sigset_t			client_set;
	int					pid;

	if (argc != 3)
	{
		write (1, "ERROR ARGS\n", 11);
		exit (-1);
	}
	ft_memset(&act_client, 0, sizeof(act_client));
	act_client.sa_sigaction = &ft_empty;
	sigemptyset(&client_set);
	sigaddset(&client_set, SIGUSR1);
	act_client.sa_mask = client_set;
	sigaction(SIGUSR1, &act_client, 0);
	pid = ft_atoi(argv[1]);
	converter (pid, argv[2]);
}