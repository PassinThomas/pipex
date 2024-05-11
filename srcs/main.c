/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:59:42 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/11 18:52:08 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	file_redir(int i, t_pipex *pipex)
{
	// redirection fichiers
	if (i == 0)
	{
		pipex->fd_in = open(pipex->infile, O_RDONLY);
		if (pipex->fd_in < 0)
			return (perror("open"), 1);
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
	}
	if (i == pipex->nb_cmd - 1)
	{
		pipex->fd_out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (pipex->fd_out < 0)
			return (perror("open"), 1);
		dup2(pipex->fd_out, STDOUT_FILENO);
		close(pipex->fd_out);
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	pipex;

	int(i) = 0;
	if (argc < 5 || !*envp)
		return (1);
	init_data(&pipex, argc, argv);
	pipex.env = find_path(envp);
	while (i < pipex.nb_cmd)
	{
		ft_pipex(&pipex, i, argv[i + 2], pipex.env);
		i++;
	}
	while (wait(NULL) > 0)
		;
	ft_free(pipex.env);
	close(pipex.fd[0]);
	return (0);
}
