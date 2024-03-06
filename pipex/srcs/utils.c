#include <stdlib.h>
#include "pipex.h"

void	check_files(t_fd *fds)
{
	if (fds->file_in < 0)
	{
		if (fds->file_out >= 0)
			close(fds->file_out);
		error_message("\n[Input File ERROR]", 0);
	}
	if (fds->file_out < 0)
	{
		close(fds->file_in);
		error_message("\n[Output File ERROR]", 0);
	}
}

void	set_args(t_args *args, int argc, char **argv, char **envp)
{
	args->argc = argc;
	args->argv = argv;
	args->envp = envp;
}

void	free_pipes(int **pipes)
{
	int	i;

	i = -1;
	if (!pipes)
	{
		while (pipes[++i])
		{
			close_fd_pair(pipes[0], pipes[1]);
			free(pipes[i]);
			pipes[i] = NULL;
		}
	}
	free(pipes);
	pipes = NULL;
}

void	close_fd_pair(int fd1, int fd2)
{
	if (close(fd1) < 0 || close(fd2) < 0)
		error_message("\n[File Close ERROR]", 0);
}

void	garbage_collector(t_fd *fds, int **pipes)
{
	free_pipes(pipes);
	close_fd_pair(fds->file_in, fds->file_out);
}

void	error_message(char const *sms, int mode)
{
	if (mode == 0)
		perror(sms);
	else
		write(1, sms, ft_strlen(sms) + 1);
	exit(EXIT_FAILURE);
}
