/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:48:45 by myanez-p          #+#    #+#             */
/*   Updated: 2023/04/18 23:16:33 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../libft/includes/libft.h"

/* on utilise un usleep pour être sûr qu'on ne rate pas un autre signal */

/* SIGUSR1 envoie des 0, SIGUSR2 envoie des 1 */

void	send_message(char *message, int pid_server)
{
	int	i;
	int	tmp;

	i = 0;
	while (message[i])
	{
		tmp = message[i];
		while (message[i] > 0)
		{
			if (message[i] % 2 == 0)
			{
				//printf("0");
				kill(pid_server, SIGUSR1);
			}
			else
			{
				//printf("1");
				kill(pid_server, SIGUSR2);
			}
			message[i] /= 2;
			usleep(100);
		}
		while (tmp < 128)
		{
			//printf("0");
			kill(pid_server, SIGUSR1);
			usleep(100);
			tmp *= 2;
		}
		i ++;
	}
}

/* le client prend en paramètre le pid du serveur et le message */

int	main(int argc, char **argv)
{
	int		pid_server;
	char	*message;

	if (argc == 3)
	{
		pid_server = ft_atoi(argv[1]);
		message = argv[2];
		send_message(message, pid_server);
	}
	else
		ft_printf("Please enter : ./client <pid_server> <your message>\n");
	return (0);
}
