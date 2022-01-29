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

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <sys/types.h>
# include <wait.h>


typedef struct s_pipeline {
	int	*array;
	int	len;
}	t_pipeline;

void	error(char *e);
void	swap(int *a, int *b);
void	close_fds(t_pipeline *pl);
void	free_string_array(char *a[]);

void	create_pipeline(t_pipeline *pl, int n_pipes, int fd_in, int fd_out);
char	*search_dirs(char *dirs[], char *slash_name);
char	*get_path(char *name, const char *envp[]);
void	exec_cmd(const char *cmd, const char *envp[], int *fd, t_pipeline *pl);

// These two are at the bottom bc according to norminette, they're misaligned
// when there's only one tab. sic.
int		exec_pipeline(int n_cmds, const char *cmds[], const char *envp[],
			t_pipeline *pl);
int		my_open(const char *file, int flags, mode_t mode);

# define HELP_MESSAGE "\
Usage: ./pipex FILE_IN CMD_1 [CMD_N]... FILE_OUT\n\
       ./pipex here_doc DELIMITER CMD_1 [CMD_N]... FILE_OUT\n"

#endif
