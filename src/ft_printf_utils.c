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

#include <ft_printf.h>

// Using uintptr_t instead of unsigned long to avoid undefined behavior
int	ft_putptr(uintptr_t nb)
{
	const char		*s;
	unsigned char	digits;

	s = "0123456789abcdef";
	digits = 0;
	if (nb <= 15)
	{
		ft_putchar(s[nb]);
		return (1);
	}
	else
	{
		if (nb >= 16)
			digits += ft_putptr(nb / 16);
		digits += ft_putptr(nb % 16);
	}
	return (digits);
}

int	ft_putnbr_base(unsigned int nb, unsigned int base)
{
	const char		*s;
	unsigned char	digits;

	s = "0123456789abcdef";
	digits = 0;
	if (nb <= base - 1)
	{
		ft_putchar(s[nb]);
		return (1);
	}
	else
	{
		if (nb >= base)
			digits += ft_putnbr_base(nb / base, base);
		digits += ft_putnbr_base(nb % base, base);
	}
	return (digits);
}

int	ft_puthex_upper(unsigned int nb)
{
	const char		*s;
	unsigned char	digits;

	s = "0123456789ABCDEF";
	digits = 0;
	if (nb <= 15)
	{
		ft_putchar(s[nb]);
		return (1);
	}
	else
	{
		if (nb >= 16)
			digits += ft_puthex_upper(nb / 16);
		digits += ft_puthex_upper(nb % 16);
	}
	return (digits);
}

int	ft_print_int(int nb)
{
	unsigned char	digits;

	digits = 0;
	if (nb >= 0 && nb <= 9)
	{
		ft_putchar('0' + nb);
		return (1);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		digits++;
		if (nb <= -10)
			digits += ft_print_int(-(nb / 10));
		digits += ft_print_int(-(nb % 10));
	}
	else
	{
		if (nb >= 10)
			digits += ft_print_int(nb / 10);
		digits += ft_print_int(nb % 10);
	}
	return (digits);
}

int	ft_print_unsigned_int(unsigned int nb)
{
	unsigned char	digits;

	digits = 0;
	if (nb <= 9)
	{
		ft_putchar('0' + nb);
		return (1);
	}
	else
	{
		if (nb >= 10)
			digits += ft_print_unsigned_int(nb / 10);
		digits += ft_print_unsigned_int(nb % 10);
	}
	return (digits);
}
