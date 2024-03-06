#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

#include "pipex.h"

void	error_message(char *text, int mode);
void	close_fd_pair(int fd1, int fd2);
void	close_pipes(int **pipes, int i);
void	garbage_collector(t_fd *fds, int **pipes, char *text, int mode);
void	free_exec(char *operand, char **paths);

#endif /* GARBAGE_COLLECTOR_H */
