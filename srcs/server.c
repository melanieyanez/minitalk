/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:48:49 by myanez-p          #+#    #+#             */
/*   Updated: 2023/04/24 11:10:06 by myanez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Handler des signaux reçus */
/* qui permet de transformer le binaire en caractères */

void	receive_message(int num_signal)
{
	static t_message	data_message;

	if (num_signal == SIGUSR2)
	{
		data_message.value += ft_pow(2, data_message.power);
		data_message.power ++;
	}
	if (num_signal == SIGUSR1)
		data_message.power ++;
	if (data_message.power > 7)
	{
		write(1, &data_message.value, 1);
		data_message.power = 0;
		data_message.value = 0;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, receive_message);
	signal(SIGUSR2, receive_message);
	while (1)
		pause();
}
