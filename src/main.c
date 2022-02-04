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

int	pipex(int argc, const char *argv[], const char *envp[])
{
	int			fd_in;
	int			fd_out;
	t_pipeline	pl;

	fd_in = my_open(argv[0], O_RDONLY, 0);
	fd_out = my_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	create_pipeline(&pl, argc - 3, fd_in, fd_out);
	return (exec_pipeline(argc - 2, &argv[1], envp, &pl));
}

char	*get_heredoc_line(void)
{
	ft_putstr("heredoc> ");
	return (get_next_line(STDIN_FILENO));
}

int	is_eof(const char *eof, const char *line)
{
	return (ft_strncmp(line, eof, ft_strlen(eof)) == 0 && \
		ft_strlen(eof) + 1 == ft_strlen(line));
}

int	pipex_heredoc(int argc, const char *argv[], const char *envp[])
{
	int			fd_heredoc[2];
	int			fd_out;
	t_pipeline	pl;
	char		*line;

	fd_out = my_open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (pipe(fd_heredoc) == -1)
		error("pipe");
	line = get_heredoc_line();
	while (line && !is_eof(argv[0], line))
	{
		write(fd_heredoc[1], line, ft_strlen(line));
		free(line);
		line = get_heredoc_line();
	}
	free(line);
	close(fd_heredoc[1]);
	create_pipeline(&pl, argc - 3, fd_heredoc[0], fd_out);
	return (exec_pipeline(argc - 2, &argv[1], envp, &pl));
}

int	main(int argc, const char *argv[], const char *envp[])
{
	int		exit_code;
	pid_t	pid;

	if (argc < 4 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 5))
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd(HELP_MESSAGE, 1);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		exit_code = pipex_heredoc(argc - 2, &argv[2], envp);
	else
		exit_code = pipex(argc - 1, &argv[1], envp);
	pid = wait(NULL);
	while (pid > 0)
	{
		ft_printf("Done with process: %d\n", pid);
		pid = wait(NULL);
	}
	exit(exit_code);
}
