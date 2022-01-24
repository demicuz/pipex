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

static char	*ft_strcpy_end(char *dest, const char *src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*r;
	char	*p;

	len = ft_strlen(s1) + ft_strlen(s2);
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	p = ft_strcpy_end(r, s1);
	while (*s2)
	{
		*p = *s2;
		p++;
		s2++;
	}
	*p = '\0';
	return (r);
}
