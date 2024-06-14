/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:41:50 by iniska            #+#    #+#             */
/*   Updated: 2024/05/06 16:42:50 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_empties(char *arv)
{
	int	i;

	i = 0;
	while (arv[i] != '\0')
	{
		if (arv[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	free_array(char ***paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free_line(paths[i], -1);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (paths[i] != NULL)
				free_line(paths[i], -1);
			i++;
		}
	}
	free (paths);
}

void	free_line(char **paths, int arc)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	if (arc == -1)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
	}
	else
	{
		while (i < arc)
		{
			if (paths[i] != NULL)
				free(paths[i]);
			i++;
		}
	}
	free(paths);
}

void	free_char_array(char ***paths, int arc)
{
	free_array(paths, arc);
}

void	clean_n_errors(t_pipes *pipe)
{
	if (pipe->fd_input != -1)
		close(pipe->fd_input);
	if (pipe->fd_output != -1)
		close(pipe->fd_output);
	if (pipe->cmd_paths != NULL)
		free_line(pipe->cmd_paths, pipe->cmd_count);
	if (pipe->cmd_args != NULL)
		free_array(pipe->cmd_args, pipe->cmd_count);
	if (pipe->is_here_doc)
		unlink(HERE_DOC_PATH);
	free(pipe);
}
