/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:19:39 by dapetros          #+#    #+#             */
/*   Updated: 2024/03/07 01:20:24 by dapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "pipex.h"

void	error_message(char *text, int mode);
void	close_fd_pair(int fd1, int fd2);
void	close_pipes(int **pipes, int i);
void	garbage_collector(t_fd *fds, int **pipes, char *text, int mode);
void	free_exec(char *operand, char **cmd, char **paths);

#endif  /* GARBAGE_COLLECTOR_H */
