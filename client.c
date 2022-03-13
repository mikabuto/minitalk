#include <signal.h>
#include "libft/libft.h"

static void	sending_char(int pid, int msg)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (msg & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(500);
	}
}

static void	client_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Message has been recieved by server!\n", 1);
		exit(0);
	}
	usleep(200);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					s_pid;
	int					i;
	
	if (argc != 3)
	{
		ft_putstr_fd("Wrong number of parameters!\n", 2);
		return (0);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = client_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	s_pid = ft_atoi(argv[1]);
	i = -1;
	while (argv[2][++i])
		sending_char(s_pid, argv[2][i]);
	sending_char(s_pid, argv[2][i]);
	while (1)
		pause();
	return (0);
}