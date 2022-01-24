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
#include "libft.h"

// Assumes *s is a valid string
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	char			*p;
	unsigned int	i;

	result = ft_strdup(s);
	if (!result)
		return (NULL);
	i = 0;
	p = result;
	while (*p)
	{
		*p = f(i, *p);
		p++;
		i++;
	}
	return (result);
}
