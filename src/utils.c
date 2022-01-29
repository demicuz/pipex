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

#include <pipex.h>

void	error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void	swap(int *a, int *b)
{
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

int	my_open(const char *file, int flags, mode_t mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flags);
	else
		fd = open(file, flags, mode);
	if (fd == -1)
		error((char *) file);
	return (fd);
}

// TODO
// Have to free pl->array, otherwise Valgrind shows a leak in create_pipeline().
// Wat?
void	close_fds(t_pipeline *pl)
{
	int	i;

	i = 0;
	while (i < pl->len)
	{
		close(pl->array[i]);
		i++;
	}
	free(pl->array);
}

void	free_string_array(char *a[])
{
	size_t	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
