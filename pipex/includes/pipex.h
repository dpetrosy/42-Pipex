#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_fd
{
	int	file_in;
	int	file_out;
}	t_fd;

typedef struct s_main_args
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_args;

int		**open_pipes(int argc, t_fd *fds);
void	pipex(int **pipes, t_args args);
void	my_exec(char **cmd, char **envp);
char	**envp_parsing(char **envp);
void	close_pipes(int **pipes, int i);

#endif	/* PIPEX_H */
