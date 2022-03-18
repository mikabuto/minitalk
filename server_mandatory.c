/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikabuto <mikabuto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:11:08 by mikabuto          #+#    #+#             */
/*   Updated: 2022/03/14 14:11:08 by mikabuto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

static void	send_sig(int c_pid)
{
	if (kill(c_pid, SIGUSR2) == -1)
		exit(0);
	ft_putchar_fd('\n', 1);
}

static void	server_handler(int sig, siginfo_t *info, void *context)
{
	static int	c_pid = 0;
	static int	bite = 0;
	static int	c = 0;

	(void)context;
	if (!c_pid || c_pid != info->si_pid)
	{
		c_pid = info->si_pid;
		bite = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c += 1 << (7 - bite);
	bite++;
	if (bite == 8)
	{
		if (c)
			ft_putchar_fd(c, 1);
		else
			send_sig(c_pid);
		c = 0;
		bite = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
