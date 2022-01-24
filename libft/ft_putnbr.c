/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2000/01/01 20:20:20 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr(int nb)
{
	if (nb >= 0 && nb <= 9)
		ft_putchar('0' + nb);
	else if (nb < 0)
	{
		ft_putchar('-');
		if (nb <= -10)
			ft_putnbr(-(nb / 10));
		ft_putnbr(-(nb % 10));
	}
	else
	{
		if (nb >= 10)
			ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
