#ifndef PIPEX_H
# define PIPEX_H

#include <stdbool.h>

typedef struct s_fd
{
	int	file_in;
	int	file_out;
}	t_fd;

int		**open_pipes(t_fd *fds, int argc);
char	**envp_parsing(char **envp);
void	my_exec(char **cmd, char **envp);
bool	pipex(int **pipes, int argc, char **argv, char **envp);

#endif	/* PIPEX_H */
