/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:06:08 by emedina-          #+#    #+#             */
/*   Updated: 2024/05/27 20:54:54 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

static int i_am_receiving_signals;

static int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	minus;

	i = 0;
	result = 0;
	minus = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * minus);
}

void  sig_handler ( int signum, siginfo_t * info, void * context)
{	
	static int readed_bits;
	
	(void) context;
	(void) info;
	i_am_receiving_signals = 1;
	if(signum == SIGUSR2)
		readed_bits++;
	else if(signum == SIGUSR1)
		ft_printf("Numero de bytes recibidos %d\n", readed_bits / 8);
}

int  char_to_bin ( char c, int pid)
{
	int itr;
	int bit_index;
	
	bit_index = 8;
	while (bit_index >= 1)
	{
		itr = 0;
		
		if((c >> bit_index) & 1)
			kill(pid,SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while(i_am_receiving_signals == 0)
		{
			if(itr == 50)
			{
				ft_printf("server no response");
				exit(EXIT_FAILURE);
			}
			itr++;
			usleep(100);
		}
		i_am_receiving_signals = 0;
		bit_index--;
	}
	return(0);
} 

int main(int argc, char *argv[]) {
    struct sigaction sa;
    char c;
    int pid;
    int byte_index;
	
	byte_index = 0;
    if (argc != 3) {
        ft_printf("tienes que meterle dos argumentos, ni mas ni menos");
        exit(EXIT_FAILURE);
    }

    pid = ft_atoi(argv[1]);

    sigemptyset(&sa.sa_mask);

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sig_handler;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error al manejar SIGUSR1");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Error al manejar SIGUSR2");
        exit(EXIT_FAILURE);
    }

    while (argv[2][byte_index++] != '\0') {
        c = argv[2][byte_index];
        char_to_bin(c, pid);
    }
    char_to_bin('\0', pid);
}
