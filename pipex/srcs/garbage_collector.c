#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "pipex.h"

void	error_message(char *text, int mode)
{
	if (mode == 0)
		perror(text);
	else if (text)
		write(1, text, ft_strlen(text) + 1);
	exit(EXIT_FAILURE);
}

void	close_fd_pair(int fd1, int fd2)
{
	if (close(fd1) < 0 || close(fd2) < 0)
		error_message("[FD Close ERROR]\n", 1);
}

void	close_pipes(int **pipes, int i)
{
	while (i >= 0)
	{
        close_fd_pair(pipes[i][0], pipes[i][1]);
		--i;
	}
}

void	garbage_collector(t_fd *fds, int **pipes, char *text, int mode)
{
	int	i;

	i = -1;
	while (pipes && pipes[++i])
	{
		close_fd_pair(pipes[i][0], pipes[i][1]);
		free(pipes[i]);
		pipes[i] = NULL;
	}
	free(pipes);
	pipes = NULL;
	close_fd_pair(fds->file_in, fds->file_out);
	if (mode != -1)
		error_message(text, mode);
}

void	free_exec(char *operand, char **paths)
{
	int	i;

	i = -1;
	free(operand);
	while (paths[++i])
		free(paths[i]);
	free(paths);
}