/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikabuto <mikabuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:10:50 by mikabuto          #+#    #+#             */
/*   Updated: 2022/03/14 14:10:50 by mikabuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

static void	sending_char(int s_pid, int msg)
{
	int	i;
	int	err;

	i = 7;
	while (i >= 0)
	{
		if (msg & (1 << i))
			err = kill(s_pid, SIGUSR1);
		else
			err = kill(s_pid, SIGUSR2);
		i--;
		usleep(500);
		if (err == -1)
		{
			ft_putstr_fd("Kill failed to send signal :(\n", 2);
			exit(0);
		}
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
