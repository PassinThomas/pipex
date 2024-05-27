/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:35:33 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/24 14:01:11 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd[2];
	int		*pid;
	int		nb_cmd;
	int		fd_in;
	int		fd_out;
	int		prev_fd;
	char	*infile;
	char	*outfile;
	char	*cmd;
	char	**path;
	int		status;
	int		here_doc;

}			t_pipex;

int			file_redir(int i, t_pipex *data);
void		init_data(t_pipex *data, int ac, char **av, char **envp);
char		**find_path(char **envp);
char		*cmd(t_pipex *data, char *command);
void		ft_execve(t_pipex *pipex, char *argv, char **envp);
void		ft_pipex(t_pipex *pipex, int i, char *argv, char **envp);

#endif