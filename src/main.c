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
	pl->len = (n_pipes + 1) * 2;
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

void	close_fds(t_pipeline *pl)
{
	int	i;

	i = 0;
	while (i < pl->len)
	{
		close(pl->array[i]);
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

char	*search_PATH(char *dirs[], char *slash_name)
{
	int		i;
	char	*abs_path;

	i = 0;
	while (dirs[i])
	{
		abs_path = ft_strjoin(dirs[i], slash_name);
		if (access(abs_path, X_OK) == 0)
			return (abs_path);
		free(abs_path);
		i++;
	}
	return (NULL);
}

// If path is not found, returns name. It will throw "No such file or directory"
// error later in exec anyway. Explicit is better than implicit. Not my case.
char	*get_path(char *name, const char *envp[])
{
	int		i;
	char	**dirs;
	char	*slash_name;
	char	*abs_path;

	if (access(name, X_OK) == 0)
		return name;
	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	dirs = ft_split(envp[i] + 5, ':');
	slash_name = ft_strjoin("/", name);
	abs_path = search_PATH(dirs, slash_name);
	free_string_array(dirs);
	free(slash_name);
	if (!abs_path)
		return (name);
	return (abs_path);
}

void	execute_cmd(const char *cmd, const char *envp[], int *fd, t_pipeline *pl)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	path = get_path(cmd_split[0], envp);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_fds(pl);
	// if (path == NULL)
	// {
	// 	// TODO maybe use printf?
	// 	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	// 	ft_putstr_fd(cmd, STDERR_FILENO);
	// 	ft_putstr_fd("\n", STDERR_FILENO);
	// 	exit(EXIT_FAILURE);
	// }
	execve(path, cmd_split, (char **) envp);
	error(cmd_split[0]);
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
		printf("created procces #%d (%d), parent: %d\n", i + 1, pid, getpid());
		i++;
	}
	close_fds(&pl);
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
		printf("Done with %d\n", wpid);
	puts("Should be finished now");
	return (EXIT_SUCCESS);
}
