#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"
#include "garbage_collector.h"

int	**open_pipes(t_fd *fds, int argc)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = (int **)malloc(sizeof(int *) * (argc - 1));
	if (!pipes)
		garbage_collector(fds, pipes, "[Malloc ERROR]\n", 1);
	pipes[argc - 2] = NULL;
	while (++i < argc - 2)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			garbage_collector(fds, pipes, "[Pipe Opening ERROR]\n", 1);
	}
	return (pipes);
}

char	**envp_parsing(char **envp)
{
	char	*envp_path;
	char	**paths;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
	envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	paths = ft_split(envp_path, ':');
	free(envp_path);
	return (paths);
}

void	my_exec(char **cmd, char **envp)
{
	char	**paths;
	char	*binary;
	char	*operand;
	int		i;

	paths = envp_parsing(envp);
	i = -1;
	while (paths[++i])
	{
		if (access(cmd[0], X_OK) == -1)
		{
			binary = ft_strjoin(paths[i], "/");
			operand = ft_strjoin(binary, cmd[0]);
			free(binary);
			if (access(operand, X_OK) == -1)
				continue ;
			execve(operand, cmd, envp);
			error_message("[Execve ERROR]", 0);
		}
		execve(cmd[0], cmd, envp);
		error_message("[Execve ERROR]", 0);
	}
	free_exec(operand, paths);
	error_message("[Access ERROR]", 0);
}

bool pipex(int **pipes, int argc, char **argv, char **envp)
{
	pid_t	id;
	int		i;

	i = -1;
	while (++i < argc - 3)
	{
		id = fork();
		if (id < 0)
			return false;
		if (id == 0)
		{
			if (dup2(pipes[i][0], 0) < 0 ||
					dup2(pipes[i + 1][1], 1) < 0)
				return false;
			close_pipes(pipes, argc - 4);
			my_exec(ft_split(argv[i + 2], ' '), envp);
		}
	}
	return true;
}
