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

char	*ft_strchr(const char *s, int c)
{
	c &= 0b11111111;
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *) s);
	else
		return (NULL);
}
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char s[] = "hello world";
// 	int c = '&';

// 	char *r = strchr(s, c);
// 	char *r2 = ft_strchr(s, c);
// 	// char *r2 = r;
// 	if (r)
// 		printf("%c\n", *r);
// 	else
// 		puts("nullptr");

// 	if (r2)
// 		printf("%c\n", *r2);
// 	else
// 		puts("nullptr");
// }
