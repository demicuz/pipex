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

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipeline {
	int	*array;
	int	len;
}	t_pipeline;

void	error(char *e);

# define HELP_MESSAGE "\
Usage: ./pipex <file_in> <cmd1> ... <cmdn> <file_out>\n\
       ./pipex here_doc <delimiter> <cmd1> ... <cmdn> <file_out>\n"

#endif
