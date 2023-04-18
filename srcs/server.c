/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melanieyanez <melanieyanez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:48:49 by myanez-p          #+#    #+#             */
/*   Updated: 2023/04/18 23:39:41 by melanieyane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../libft/includes/libft.h"

/* le serveur doit être lancé en premier et afficher son pid */
/* le serveur doit recevoir le message et l'afficher */
/* bonus: accusé de réception */

/* on utilise plutôt sigaction que signal car plus récent */
/* mais signal est quand même plus simple */

/* je dois transformer mon binaire en int */

/* je dois créer une static structure */

int	ft_pow(int base, int power)
{
	int	base_i;

	base_i = base;
	if (power == 0)
		base = 1;
	while ((power - 1) > 0)
	{
		base *= base_i;
		power --;
	}
	return (base);
}

void	receive_message(int num_signal)
{
	static int			value;
	static int			power;

	if (num_signal == SIGUSR2)
	{
		//printf("1");
		value += ft_pow(2, power);
		power ++;
	}
	if (num_signal == SIGUSR1)
	{
		//printf("0");
		power ++;
	}
	if (power > 7)
	{
		write(1, &value, 1);
		power = 0;
		value = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, receive_message);
	signal(SIGUSR2, receive_message);
	while (1)
		pause();
}
