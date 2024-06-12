/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:22:34 by iniska            #+#    #+#             */
/*   Updated: 2024/01/30 13:23:19 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes(t_pipes *pipe)
{
	pipe->fd_input = -1;
	pipe->fd_output = -1;
	pipe->cmd_paths = NULL;
	pipe->cmd_args = NULL;
	pipe->is_valid_intake = false;
	pipe->is_here_doc = false;
	pipe->cmd_count = 0;
}
