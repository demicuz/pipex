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

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pipex.h>
#include <stdlib.h>
#include <fcntl.h>
// #include <limits.h>

#include <libft.h>
#include <pipex.h>

// if (access("/usr/bin/wc", X_OK) != 0)
// {
// 	perror("access");
// }
// else
// 	puts("can access");

void	clean_pipes()
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	do_me(const char *command)
{

}

int	my_open(const char *file, int flags, mode_t mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flags);
	else
		fd = open(file, flags, mode);
	if (fd == -1)
		error("file");
	return (fd);
}

void	execute_commands(int argc, const char *argv[], const char *envp[])
{
	int fd_in = my_open(argv[0], O_RDONLY, 0);
	int fd_out = my_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (access("my_echo", X_OK) == -1)
		error("access");
	else
	{
		char *cmd[] = { (char*) "my_echo", "hello", "world", 0 };
		puts(cmd[0]);
		if (execve("my_echo", cmd, (char**) envp) == -1)
			error("execve");
	}
	// execute_commands(argc - 3, &(argv[2]), fd_in, fd_out);
}

int main(int argc, const char *argv[], const char *envp[])
{
	if (argc >= 5)
		execute_commands(argc - 1, &argv[1], envp);
	else
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd(HELP_MESSAGE, 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
