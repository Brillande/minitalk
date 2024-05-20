/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:05:47 by emedina-          #+#    #+#             */
/*   Updated: 2024/04/26 16:09:18 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	bit_handler(int bit)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	c += ((bit & 1) << i);
	i++;
	if (i == 7)
	{
		ft_printf("%c", c);
		if (!c)
			ft_printf("\n");
	}
}

int	main(void)
{
	ft_printf("My Server PID is: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR2, bit_handler);
		signal(SIGUSR1, bit_handler);
		pause();
	}
	return (0);
}
