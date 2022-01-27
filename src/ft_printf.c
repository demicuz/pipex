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
#include <stdarg.h>

char	*ft_strshift(char *str, int n)
{
	while (n > 0 && *str)
	{
		str++;
		n--;
	}
	return (str);
}

// Norminette: "Preprocessors can be used only in the global scope" Yeah.
int	ft_print_pointer(uintptr_t p)
#ifdef __linux__

{
	if (!p)
		return (write(1, "(nil)", 5));
	else
		return (write(1, "0x", 2) + ft_putptr(p));
}
#else

{
	if (!p)
		return (write(1, "0x0", 3));
	else
		return (write(1, "0x", 2) + ft_putptr(p));
}
#endif

int	ft_print_str(char *s)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s);
		return (write(1, s, len));
	}
	else
		return (write(1, "(null)", 6));
}

int	ft_resolve_and_print(va_list *args, char *pos)
{
	if (*pos == 'c')
	{
		ft_putchar(va_arg(*args, int));
		return (1);
	}
	else if (*pos == 's')
		return (ft_print_str(va_arg(*args, char *)));
	else if (*pos == 'p')
		return (ft_print_pointer((uintptr_t) va_arg(*args, void *)));
	else if (*pos == 'd' || *pos == 'i')
		return (ft_print_int(va_arg(*args, int)));
	else if (*pos == 'u')
		return (ft_putnbr_base(va_arg(*args, unsigned int), 10));
	else if (*pos == 'x')
		return (ft_putnbr_base(va_arg(*args, unsigned int), 16));
	else if (*pos == 'X')
		return (ft_puthex_upper(va_arg(*args, unsigned int)));
	else
	{
		ft_putchar('%');
		return (1);
	}
}

// Taking a naive approach (assuming no flags, precision, etc.)
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	char	*pos;

	va_start(args, format);
	len = 0;
	pos = ft_strchr(format, '%');
	while (pos)
	{
		len += write(1, format, pos - format);
		len += ft_resolve_and_print(&args, pos + 1);
		format = ft_strshift(pos, 2);
		pos = ft_strchr(format, '%');
	}
	len += write(1, format, ft_strlen(format));
	va_end(args);
	return (len);
}
