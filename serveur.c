#include "minitalk.h"

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

static void	pid_number (void)
{
	static char	reverse_pid[10] = "";
	static char	char_pid[10] = "";
	size_t		len;
	size_t		pid;
	size_t		i;

	pid = getpid();
	len = 0;
	i = 0;
	if (pid <= 0)
		write (1, "WRONG PID", 9);
	while (pid > 0)
	{
		reverse_pid[i] = (pid % 10) + '0';
		pid /= 10;
		i++;
	}
	len = i - 1;
	i = 0;
	while (reverse_pid[i])
		char_pid[i++] = reverse_pid[len--];
	write (1, "My pid is: ", 11);
	write (1, char_pid, sizeof(char_pid));
	write (1, "\n", 1);
}

static void	sighandler(int signum, siginfo_t *info_list,
	__attribute__ ((unused))void *no_name)
{
	static size_t	count = 128;
	static char		c = 0;

	if (count == 0)
	{
		count = 128;
		c = 0;
	}
	if (signum == SIGUSR1)
	{
		c += count;
		count /= 2;
	}
	else
		count /=2;
	if (count == 0)
		write (1, &c, 1);
	usleep (30);
	kill(info_list->si_pid, SIGUSR1);
}

int	main (void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = &sighandler;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_mask = set;
	pid_number();
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
	{
	}
	return (0);
}