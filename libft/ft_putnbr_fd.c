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

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n <= 9)
	{
		ft_putchar_fd('0' + n, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n <= -10)
			ft_putnbr_fd(-(n / 10), fd);
		ft_putnbr_fd(-(n % 10), fd);
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
