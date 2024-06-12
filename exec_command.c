/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:46:16 by iniska            #+#    #+#             */
/*   Updated: 2024/01/26 09:51:39 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	shut_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

t_bool	fork_it(t_pipes *pipes, int fd[2], pid_t *pid, int index)
{
	if (pipe(fd) == -1)
		return (false);
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		shut_fd(fd);
		return (false);
	}
	if (*pid == 0)
	{
		if (index == 0)
			dup2(pipes->fd_input, STDIN_FILENO);
		if (index == pipes->cmd_count - 1)
			dup2(pipes->fd_output, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		shut_fd(fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
	return (true);
}

static t_bool	wait_it(t_pipes *pipe, pid_t pid, int index, int *fd)
{
	int	status;

	close(fd[0]);
	if (index == pipe->cmd_count - 1)
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (false);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (false);
	}
	return (true);
}

int	create_child(t_pipes *pipe, char **envp, int index)
{
	pid_t	pid;
	int		fd[2];

	if (!fork_it(pipe, fd, &pid, index))
		return (false);
	if (pid == 0)
	{
		if (pipe->cmd_paths[index])
			execve(pipe->cmd_paths[index], pipe->cmd_args[index], envp);
		else
		{
			perror("command not found");
			clean_n_errors(pipe);
			exit(1);
		}
	}
	else
		wait_it(pipe, pid, index, fd);
	return (true);
}
