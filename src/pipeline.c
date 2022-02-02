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

#include "libft.h"
#include <pipex.h>
#include <stdlib.h>

// TODO It's a bad approach. If we have a lot of commands, it opens a ton of
// file descriptors and closes them in each child process. Supports up to about
// 500 piped commands. Which is certainly enough, but an unnecessary limitation
// anyway.
// ---
// Returns an array of ints. Every pair corresponds to read/write fd.
// The first one is fd_in, then pipes, the last one is fd_out:
// {file_in, pipe1_out, pipe1_in, ..., pipeN_out, pipeN_in, file_out}
// n_pipes can be zero
void	create_pipeline(t_pipeline *pl, int n_pipes, int fd_in, int fd_out)
{
	int	i;
	int	fd[2];

	pl->array = malloc(sizeof(int) * (n_pipes * 2 + 2));
	if (pl->array == NULL)
		error("malloc");
	pl->len = n_pipes * 2 + 2;
	pl->array[0] = fd_in;
	pl->array[pl->len - 1] = fd_out;
	i = 0;
	while (i < n_pipes)
	{
		if (pipe(fd) == -1)
			error("pipe");
		pl->array[i * 2 + 2] = fd[0];
		pl->array[i * 2 + 1] = fd[1];
		i++;
	}
}

char	*search_dirs(char *dirs[], char *slash_name)
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
		return (name);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	dirs = ft_split(envp[i] + 5, ':');
	slash_name = ft_strjoin("/", name);
	abs_path = search_dirs(dirs, slash_name);
	free_string_array(dirs);
	free(slash_name);
	if (!abs_path)
		return (name);
	return (abs_path);
}

// TODO maybe create ft_printf_fd or something?
void	exec_cmd(const char *cmd, const char *envp[], int *fd, t_pipeline *pl)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	path = get_path(cmd_split[0], envp);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_fds(pl);
	execve(path, cmd_split, (char **) envp);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd_split[0], 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

// TODO maybe return the last command's exit code somehow?
// In case of a fork error if I just call error("fork") and parent has
// children, those become zombies (I think). But they should get killed by init.
int	exec_pipeline(int n_cmds, const char *cmds[], const char *envp[],
	t_pipeline *pl)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < n_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr("Error creating a fork\n");
			close_fds(pl);
			return (EXIT_FAILURE);
		}
		else if (pid == 0)
			exec_cmd(cmds[i], envp, &pl->array[i * 2], pl);
		ft_printf("created procces #%d: %d\n", i + 1, pid);
		i++;
	}
	close_fds(pl);
	return (EXIT_SUCCESS);
}
