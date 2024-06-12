/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:04:29 by iniska            #+#    #+#             */
/*   Updated: 2024/05/07 16:50:18 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// CHECK THIS
int	get_infile(t_pipes *pipe, char **arv)
{
	int	fd;

	if (arv == NULL)
		return (-1);
	if (pipe->is_here_doc)
	{
		handle_the_dog(arv[2]);
		pipe->fd_input = open(HERE_DOC_PATH, O_RDONLY);
		if (pipe->fd_input == -1)
		{
			perror("Error opening input file");
			return (-1);
		}
	}
	else
	{
		fd = open(arv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening input file");
			return (-1);
		}
		pipe->fd_input = fd;
	}
	return (pipe->fd_input);
}

int	get_outfile(t_pipes *p, char **a, int arc)
{
	if (p->is_here_doc)
		p->fd_output = (open(a[arc - 1], O_WRONLY | O_APPEND | O_CREAT));
	else
		p->fd_output = (open(a[arc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644));
	if (p->fd_output == -1)
	{
		clean_n_errors(p);
		perror("Error opening output file");
		exit(1);
	}
	return (p->fd_output);
}

t_bool	check_arguments(t_pipes *pipe, int arc, char **arv)
{
	if (arv[1] && ft_strncmp(arv[1], "here_doc", 8) == 0
		&& ft_strlen(arv[1]) == 8)
		pipe->is_here_doc = true;
	if (arc < 5 + (int)pipe->is_here_doc)
		return (false);
	if (get_infile(pipe, arv) == -1)
	{
		perror("infile does not work\n");
		return (false);
	}
	if (get_outfile(pipe, arv, arc) == -1)
	{
		perror("bad arguments! \n");
		return (false);
	}
	pipe->cmd_count = arc - 3 - pipe->is_here_doc;
	return (true);
}
