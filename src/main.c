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
	{
		if (flags == O_RDONLY)
			error("file read");
		else
			error("file write");
	}
	return (fd);
}

// Returns an array of ints. Every pair corresponds to pipe read/write.
int	*create_pipes(int n)
{
	int *pipes;
	int i;
	int ret;

	pipes = malloc(sizeof(int *) * n * 2);
	if (pipes == NULL)
		error("malloc");
	i = 0;
	while (i < n)
	{
		ret = pipe(&pipes[i * 2]);
		if (ret == -1)
			error("pipe");
		i++;
	}
	return pipes;
}

void	execute_command(const char *cmd, char **envp, int fd_in, int fd_out)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	// TODO check if can access command
	execve(cmd_split[0], cmd_split, envp);
}

void	pipex(int argc, const char *argv[], const char *envp[])
{
	int	fd_in;
	int	fd_out;
	int	*pipes;

	fd_in = my_open(argv[0], O_RDONLY, 0);
	fd_out = my_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	pipes = create_pipes(argc - 3);
	if (access("my_echo", X_OK) == -1)
		error("access");
	else
	{
		char *cmd[] = { (char*) "my_echo", "hello", "world", 0 };
		puts(cmd[0]);
		if (execve("my_echo", cmd, (char**) envp) == -1)
			error("execve");
	}
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
