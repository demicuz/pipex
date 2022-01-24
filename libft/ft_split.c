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

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;
	char	in_word;

	if (c == '\0')
		return (*s != '\0');
	words = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = 1;
			words++;
		}
		else if (in_word && *s == c)
			in_word = 0;
		s++;
	}
	return (words);
}

// absolutely wicked. moves *s, puts a word in *p.
static void	ft_put_word(char **p, char **s, char c)
{
	char	*word_start;
	size_t	word_len;

	while (**s == c)
		(*s)++;
	word_start = *s;
	while (**s && **s != c)
		(*s)++;
	word_len = *s - word_start;
	*p = malloc(sizeof(char) * (word_len + 1));
	if (!*p)
		return ;
	ft_strlcpy(*p, word_start, word_len + 1);
}

static void	ft_free_all(char **words)
{
	char	**p;

	p = words;
	while (*p)
	{
		p++;
		free(p[-1]);
	}
	free(words);
}

// "__hello__world__", '_' --> {"hello", "world", NULL}
// "hello", '\0' --> {"hello", NULL}
char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**result;
	char	**p;

	word_count = ft_count_words(s, c);
	result = ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	p = result;
	while (word_count)
	{
		ft_put_word(p, (char **) &s, c);
		if (!*p)
		{
			ft_free_all(result);
			return (NULL);
		}
		word_count--;
		p++;
	}
	return (result);
}
