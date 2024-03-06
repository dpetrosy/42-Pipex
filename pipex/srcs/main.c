#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include "pipex.h"
#include "utils.h"

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	t_fd	fds;
	t_args	args;

	if (argc < 5)
		error_message("[Arguments ERROR]: Arguments minimum count: 5\n", 1);
	fds.file_in = open(argv[1], O_RDONLY);
	fds.file_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	check_files(&fds);
	set_args(&args, argc, argv, envp);
	pipes = open_pipes(argc, &fds);




	dup2(fds.file_in, pipes[0][0]);
	dup2(fds.file_out, pipes[argc - 3][1]);
	pipex(pipes, args);
	close_pipes(pipes, args.argc - 4);
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	garbage_collector(&fds, pipes, args.argc - 2);
	return (0);
}
