/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.f              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:16:47 by iniska            #+#    #+#             */
/*   Updated: 2024/05/09 10:17:01 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "/Users/iniska/Desktop/Code/libft/libft.h"

t_bool	parse_cmd_args(t_pipes *pipe, int arc, char **arv)
{
	int		i;
	char	**args;

	pipe->cmd_args = ft_calloc(sizeof(char **), (arc - 2 - pipe->is_here_doc));
	if (!pipe->cmd_args)
		return (false);
	i = 1 + pipe->is_here_doc;
	while (i++ < arc - 1)
	{
		args = ft_split(arv[i], ' ');
		if (!args)
		{
			free_char_array(pipe->cmd_args, arc - 2 - pipe->is_here_doc);
			pipe->cmd_args = NULL;
			return (false);
		}
		pipe->cmd_args[i - 2 - pipe->is_here_doc] = args;
	}
	return (true);
}
