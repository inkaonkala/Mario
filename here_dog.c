/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:50:53 by iniska            #+#    #+#             */
/*   Updated: 2024/05/20 17:51:41 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "/Users/iniska/Desktop/Code/libft/libft.h"

// write get line!
void	handle_the_dog(const char *arv)
{
	int		fd;
	char	*line;

	fd = open(HERE_DOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit (1);
	ft_printf("heredoc> ");
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, arv, ft_strlen(arv)) == 0
			&& line[ft_strlen(arv)] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(fd);
}
