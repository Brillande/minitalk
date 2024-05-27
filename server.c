/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:47 by emedina-          #+#    #+#             */
/*   Updated: 2024/05/27 21:21:33 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	bin_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
	{
		*c = (*c << 1) | 1;
	}
	else if (signum == SIGUSR2)
	{
		*c <<= 1;
	}
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid;
	static int	i ;
	static char	c ;
	
	(void)context;
	if (pid == 0)
	{
		pid = info->si_pid;
	}
	bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		ft_putchar_fd(c,1);
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction sa;

	printf("Server PID: %d\n", getpid());

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction1");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction2");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		pause();
	}
}
