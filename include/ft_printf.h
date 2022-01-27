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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <inttypes.h>
# include <libft.h>

int	ft_printf(const char *format, ...);
int	ft_putptr(uintptr_t nb);
int	ft_putnbr_base(unsigned int nb, unsigned int base);
int	ft_puthex_upper(unsigned int nb);
int	ft_print_int(int nb);
int	ft_print_unsigned_int(unsigned int nb);

#endif
