/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:55:40 by iniska            #+#    #+#             */
/*   Updated: 2024/01/26 10:01:27 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "/Users/iniska/Desktop/Code/libft/libft.h"
# define HERE_DOC_PATH "/tmp/here_doc.txt"

typedef enum s_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_pipes
{
	int		fd_input;
	int		fd_output;

	char	**cmd_paths;
	char	***cmd_args;

	t_bool	is_valid_intake;
	t_bool	is_here_doc;

	int		cmd_count;
}	t_pipes;

// in init pipes
void	init_pipes(t_pipes *pipe_struct);

// in command_line.c

t_bool	parse_cmd_line(t_pipes *pipe, int arc, char **arv, char **envp);

// in  arguments.c

t_bool	parse_cmd_args(t_pipes *pipe, int arc, char **arv);

//files.c

int		get_infile(t_pipes *pipe, char **arv);
int		get_outfile(t_pipes *pipe, char **arv, int arc);
t_bool	check_arguments(t_pipes *pipe, int arc, char **arv);

// exec_commands

t_bool	fork_it(t_pipes *pipe, int fd[2], pid_t *pid, int index);
int		create_child(t_pipes *pipe, char **envp, int index);

//clean_n_errors

int		check_empties(char *arv);
void	free_line(char **paths, int arc);
void	free_array(char ***paths, int arc);
void	clean_n_errors(t_pipes *pipe);
void	free_char_array(char ***paths, int arc);

// here_dog!

void	handle_the_dog(const char *arv);

#endif
