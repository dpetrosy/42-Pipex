/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:20:36 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/07 01:21:58 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "pipex.h"
#include "garbage_collector.h"

void	open_files(t_fd *fds, int argc, char **argv)
{
	fds->file_in = open(argv[1], O_RDONLY);
	if (fds->file_in < 0)
		error_message("[Input File ERROR]: ", 0);
	fds->file_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds->file_out < 0)
	{
		close(fds->file_in);
		error_message("[Output File ERROR]: ", 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	t_fd	fds;

	if (argc < 5)
		error_message("[Arguments ERROR]: Arguments minimum count: 5\n", 1);
	open_files(&fds, argc, argv);
	pipes = open_pipes(&fds, argc);
	if (dup2(fds.file_in, pipes[0][0]) < 0 ||
			dup2(fds.file_out, pipes[argc - 3][1]) < 0)
		garbage_collector(&fds, pipes, "[Dup2 Error]: \n", 0);
	if (pipex(pipes, argc, argv, envp) == false)
		garbage_collector(&fds, pipes, "[Fork Error]\n", 1);
	close_pipes(pipes, argc - 4);
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	close_fd_pair(pipes[argc - 3][0], pipes[argc - 3][1]);
	close_fd_pair(fds.file_in, fds.file_out);
	return (0);
}
