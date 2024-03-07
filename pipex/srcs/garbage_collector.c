/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:22:15 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/07 01:22:37 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	close(fd1);
	close(fd2);
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
	error_message(text, mode);
}

void	free_exec(char *operand, char **cmd, char **paths)
{
	int	i;

	i = -1;
	free(operand);
	if (cmd)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	i = -1;
	if (paths)
	{
		while (paths[++i])
			free(paths[i]);
		free(paths);
	}
}
