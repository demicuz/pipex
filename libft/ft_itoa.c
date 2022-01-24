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

#include <stdlib.h>

static int	ft_count_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		n_digits;
	int		is_negative;
	int		i;
	char	*result;

	n_digits = ft_count_digits(n);
	is_negative = (n < 0);
	result = malloc(sizeof(char) * (n_digits + is_negative + 1));
	if (!result)
		return (NULL);
	if (is_negative)
		result[0] = '-';
	i = n_digits - 1 + is_negative;
	result[i + 1] = '\0';
	while (i >= is_negative)
	{
		if (is_negative)
			result[i] = -(n % 10) + '0';
		else
			result[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (result);
}
