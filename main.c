/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:55:13 by iniska            #+#    #+#             */
/*   Updated: 2024/01/23 15:10:36 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_bool	handle_commands(t_pipes *pipe, int arc, char **arv, char **envp)
{
	if (!check_arguments(pipe, arc, arv))
	{
		clean_n_errors(pipe);
		return (false);
	}
	if (!parse_cmd_line(pipe, arc, arv, envp))
	{
		clean_n_errors(pipe);
		return (false);
	}
	if (!parse_cmd_args(pipe, arc, arv))
	{
		clean_n_errors(pipe);
		return (false);
	}
	return (true);
}

static int	pipex(int arc, char **arv, char **envp)
{
	t_pipes	*pipe;
	int		i;

	pipe = malloc(sizeof(t_pipes));
	if (!pipe)
		exit (1);
	init_pipes(pipe);
	if (!handle_commands(pipe, arc, arv, envp))
	{
		ft_printf("Bananas! Commands failed\n");
		return (1);
	}
	i = -1;
	while (i++ < pipe->cmd_count)
	{
		if (!create_child(pipe, envp, i))
			break ;
	}
	i = -1;
	while (i++ < pipe->cmd_count)
		wait(NULL);
	close(pipe->fd_input);
	close(pipe->fd_output);
	return (0);
}

static int	arv_check(int arc, char **arv)
{
	int	i;

	i = 1;
	while (i < arc)
	{
		if (ft_strlen(arv[i]) == 0)
		{
			ft_printf("Bananas!: Empty command!\n");
			return (1);
		}
		i++;
	}
	i = 1;
	while (i < arc)
	{
		if (check_empties(arv[i]) > 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int arc, char **arv, char **envp)
{
	if (arv_check(arc, arv) > 0)
		exit(1);
	if (arc == 5)
		pipex(arc, arv, envp);
	else
		ft_printf("Bananas!: Wrong amount of arguments\n");
	return (0);
}

//	ft_printf("%s\n", pipe->cmd_paths[1])
