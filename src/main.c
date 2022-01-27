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

int	my_open(const char *file, int flags, mode_t mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flags);
	else
		fd = open(file, flags, mode);
	if (fd == -1)
	{
		if (flags == O_RDONLY)
			error("file read");
		else
			error("file write");
	}
	return (fd);
}

// Returns an array of ints. Every pair corresponds to read/write fd.
// The first one is fd_in, then pipes, the last one is fd_out.
int	*create_pipeline(int n_pipes, int fd_in, int fd_out)
{
	int *pipeline;
	int i;
	int ret;

	pipeline = malloc(sizeof(int *) * (n_pipes * 2 + 2));
	if (pipeline == NULL)
		error("malloc");
	pipeline[0] = fd_in;
	pipeline[n_pipes * 2 + 1] = fd_out;
	i = 0;
	while (i < n_pipes)
	{
		ret = pipe(&pipeline[i * 2 + 1]);
		if (ret == -1)
			error("pipe");
		i++;
	}
	return pipeline;
}

// void	execute_command(const char *cmd, char **envp, int fd_in, int fd_out)
// {
// 	char	**cmd_split;

// 	cmd_split = ft_split(cmd, ' ');
// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// 	close(fd_in);
// 	close(fd_out);
// 	// TODO check if can access command
// 	// if (access("my_echo", X_OK) == -1)
// 	// 	error("access");
// 	execve(cmd_split[0], cmd_split, envp);
// 	error("execve");
// }

void	execute_command(const char *cmd, char **envp, int *fd)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	// TODO close all
	close(fd[0]);
	close(fd[1]);
	// TODO check if can access command
	// if (access("my_echo", X_OK) == -1)
	// 	error("access");
	execve(cmd_split[0], cmd_split, envp);
	error("execve");
}

// void	spawn(const char *cmd, **envp)
// {

// }

void	pipex(int argc, const char *argv[], const char *envp[])
{
	int	fd_in;
	int	fd_out;
	int	*pipes;
	int	i;
	pid_t pid;

	fd_in = my_open(argv[0], O_RDONLY, 0);
	fd_out = my_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	pipes = create_pipeline(argc - 3, fd_in, fd_out);
	i = 0;
	// while (i < argc - 1)
	// {

	// }
}

int main(int argc, const char *argv[], const char *envp[])
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd(HELP_MESSAGE, 1);
		return (EXIT_FAILURE);
	}
	pipex(argc - 1, &argv[1], envp);
	return (EXIT_SUCCESS);
}
