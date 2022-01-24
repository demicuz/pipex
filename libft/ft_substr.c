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

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_len;
	char	*sub;
	char	*p;

	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	sub_len = min(len, s_len - start);
	sub = malloc(sizeof(char) * (sub_len + 1));
	if (!sub)
		return (NULL);
	p = sub;
	s += start;
	while (sub_len)
	{
		*p = *s;
		p++;
		s++;
		sub_len--;
	}
	*p = '\0';
	return (sub);
}
