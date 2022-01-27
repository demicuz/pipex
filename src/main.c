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
#include <wait.h>
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

void	swap(int *a, int *b) {
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

// Returns an array of ints. Every pair corresponds to read/write fd.
// The first one is fd_in, then pipes, the last one is fd_out.
// {file_in, pipe1_out, pipe1_in, ..., pipen_out, pipen_in, file_out}
void	create_pipeline(t_pipeline *pl, int n_pipes, int fd_in, int fd_out)
{
	int i;
	int ret;

	pl->array = malloc(sizeof(int *) * (n_pipes * 2 + 2));
	if (pl->array == NULL)
		error("malloc");
	pl->array[0] = fd_in;
	pl->array[n_pipes * 2 + 1] = fd_out;
	i = 0;
	while (i < n_pipes)
	{
		ret = pipe(&pl->array[i * 2 + 1]);
		if (ret == -1)
			error("pipe");
		swap(&pl->array[i * 2 + 1], &pl->array[i * 2 + 2]);
		i++;
	}
}

// void	execute_cmd(const char *cmd, char **envp, int fd_in, int fd_out)
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

void	close_fds(t_pipeline *pl)
{
	int	i;

	i = 0;
	while (i < pl->len)
	{
		close(pl->array[i * 2]);
		close(pl->array[i * 2 + 1]);
		i++;
	}
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

char	*get_absolute_path(char *name, const char *envp[])
{
	int		i;
	char	**dirs;
	char	*slash_name;
	char	*abs_path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	dirs = ft_split(envp[i] + 5, ':');
	slash_name = ft_strjoin("/", name);
	i = 0;
	while (dirs[i])
	{
		abs_path = ft_strjoin(dirs[i], slash_name);
		if (access(abs_path, X_OK) == 0)
			break;
		free(abs_path);
		i++;
	}
	free_string_array(dirs);
	free(slash_name);
	return (abs_path);
}

void	execute_cmd(const char *cmd, const char *envp[], int *fd, t_pipeline *pl)
{
	char	**cmd_split;
	char	*abs_path;

	cmd_split = ft_split(cmd, ' ');
	abs_path = get_absolute_path(cmd_split[0], envp);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_fds(pl);
	// TODO check if can access command
	if (abs_path == NULL)
	{
		// TODO maybe use printf?
		ft_putstr("Command not found: ");
		ft_putstr(cmd);
		ft_putstr("\n");
		exit(EXIT_FAILURE);
	}
	execve(abs_path, cmd_split, (char **) envp);
	error("execve");
}

// void	spawn(const char *cmd, **envp)
// {

// }

// Close all but needed in/out descriptors
void	close_unused_fds(int *pipeline, int len, int i_exclude)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i == i_exclude)
		{
			i++;
			continue ;
		}
		close(pipeline[i * 2]);
		close(pipeline[i * 2 + 1]);
		i++;
	}
}

void	pipex(int argc, const char *argv[], const char *envp[])
{
	int	fd_in;
	int	fd_out;
	t_pipeline pl;
	int	i;
	pid_t pid;

	fd_in = my_open(argv[0], O_RDONLY, 0);
	fd_out = my_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	create_pipeline(&pl, argc - 3, fd_in, fd_out);
	i = 0;
	while (i < argc - 2)
	{
		printf("forking process number %d\n", i);
		pid = fork();
		if (pid == -1)
		{
			ft_putstr("Error creating a fork\n");
			return ;
			// TODO if I just call error("fork") and parent has children, those
			// become zombies in case of error (I think)
			// error("fork");
		}
		else if (pid == 0)
			execute_cmd(argv[i + 1], envp, &pl.array[i * 2], &pl);
		i++;
	}
}

int main(int argc, const char *argv[], const char *envp[])
{
	pid_t	wpid;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd(HELP_MESSAGE, 1);
		return (EXIT_FAILURE);
	}
	pipex(argc - 1, &argv[1], envp);
	while ((wpid = wait(NULL)) > 0)
		printf("Done with process %d\n", wpid);
	puts("Should be finished now");
	return (EXIT_SUCCESS);
}
