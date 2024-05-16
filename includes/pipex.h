/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:35:33 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:30:38 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
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
	char	**env;
	int		status;
}			t_pipex;

int			file_redir(int i, t_pipex *data);
void		init_data(t_pipex *data, int ac, char **av);
char		**find_path(char **envp);
char		*cmd(t_pipex *data, char *command);
void		ft_execve(t_pipex *pipex, char *argv, char **envp);
void		ft_pipex(t_pipex *pipex, int i, char *argv, char **envp);

#endif