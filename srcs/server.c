/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myanez-p <myanez-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:48:49 by myanez-p          #+#    #+#             */
/*   Updated: 2023/04/18 16:56:37 by myanez-p         ###   ########.fr       */
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

int	ft_pow(int base, int power)
{
	int	base_i;
	
	base_i = base;
	while (power - 1)
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

	if (!value)
		value = 0;
	if (!power)
		power = 0;
	if (num_signal == SIGUSR1)
	{
		printf("1");
		value += ft_pow(2, power);
		power ++;
	}
	else
	{
		printf("0");
		power ++;
	}
	if (power == 8)
	{
		printf(" value: %d\n", value);
		power = 0;
		value = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	ft_printf("resultat : %d\n", ft_pow(2, 3));
	signal(SIGUSR1, receive_message);
	signal(SIGUSR2, receive_message);
	while (42)
		pause();
}
