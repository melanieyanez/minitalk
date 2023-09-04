/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:48:45 by myanez-p          #+#    #+#             */
/*   Updated: 2023/09/04 17:06:05 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Fonction envoyant les caractères du message en paramètres */
/* sous forme binaire */

void	send_message(char *message, int pid_server)
{
	int	i;
	int	tmp;

	i = 0;
	while (message[i])
	{
		if (message[i] >= 0 && message[i] <= 127)
		{
			tmp = message[i];
			while (message[i] > 0)
			{
				if (message[i] % 2 == 0)
					kill(pid_server, SIGUSR1);
				else
					kill(pid_server, SIGUSR2);
				message[i] /= 2;
				usleep(100);
			}
			while (tmp < 128)
			{
				kill(pid_server, SIGUSR1);
				usleep(100);
				tmp *= 2;
			}
		}
		i++;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

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
