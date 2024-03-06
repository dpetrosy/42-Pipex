#ifndef UTILS_H
# define UTILS_H

void	check_files(t_fd *fds);
void	set_args(t_args *args, int argc, char **argv, char **envp);
void	free_pipes(int **pipes);



void	garbage_collector(t_fd *fds, int **pipes);
void	error_message(char const *sms, int mode);


#endif /* UTILS_H */
