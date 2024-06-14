/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:14:58 by iniska            #+#    #+#             */
/*   Updated: 2024/05/09 10:15:15 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "/Users/iniska/Desktop/Code/libft/libft.h"

static char	*extrct_path(char *path, char **envp)
{
	int	i;

	i = 0;
	while (envp[i++] != NULL)
	{
		if (ft_strncmp(path, envp[i], ft_strlen(path)) == 0
			&& envp[i][ft_strlen(path)] == '=')
			return (ft_strchr(envp[i], '=') + 1);
	}
	return (NULL);
}

static char	**find_path_env(char **envp)
{
	char	*path;

	path = extrct_path("PATH", envp);
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

static char	*const_and_check(char *paths, char *path_name)
{
	char	*oneline;
	char	*full_path;

	oneline = ft_strjoin(paths, "/");
	if (!oneline)
		return (NULL);
	full_path = ft_strjoin(oneline, path_name);
	free(oneline);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*get_path(char *path_name, char **envp)
{
	int		i;
	char	*full_path;
	char	**paths;

	if (access(path_name, F_OK) == 0)
		return (ft_substr(path_name, 0, ft_strlen(path_name)));
	paths = find_path_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = const_and_check(paths[i], path_name);
		if (full_path)
		{
			free_line(paths, -1);
			return (full_path);
		}
		i++;
	}
	return (free_line(paths, -1), NULL);
}

t_bool	parse_cmd_line(t_pipes *pipe, int arc, char **arv, char **envp)
{
	unsigned int		i;
	char				**cmd;

	pipe->cmd_paths = ft_calloc(sizeof(char *), (arc - 2 - pipe->is_here_doc));
	if (!pipe->cmd_paths)
		return (false);
	i = 1 + pipe->is_here_doc;
	while ((int)i++ < arc - 1)
	{
		cmd = ft_split(arv[i], ' ');
		if (!cmd)
		{
			free_line(pipe->cmd_paths, arc - 2 - pipe->is_here_doc);
			pipe->cmd_paths = NULL;
			return (false);
		}
		pipe->cmd_paths[i - 2 - pipe->is_here_doc] = get_path(cmd[0], envp);
		free_line(cmd, -1);
	}
	i = 0;
	while (i < arc - 2 - pipe->is_here_doc)
		i++;
	return (true);
}
