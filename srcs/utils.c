/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:50:14 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/08 18:41:34 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_data(t_pipex *data, int ac, char **av)
{
	data->prev_fd = -1;
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->nb_cmd = ac - 3;
}

char	**find_path(char **envp)
{
	char	*str;
	char	**split;

	int(i) = 0;
	int(j) = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			split = ft_split(envp[i] + 5, ':');
			while (split[j++])
			{
				str = ft_strdup(split[j]);
				free(split[j]);
				split[j] = ft_strjoin(str, "/");
				free(str);
			}
			return (split);
		}
		i++;
	}
	return (NULL);
}

char	*cmd(t_pipex *data, char *command)
{
	char	*str;
	int		i;

	i = 0;
	if (ft_strchr(command, '/'))
		data->cmd = ft_strdup(command);
	if (!data->cmd)
		return (NULL);
	while (data->env[i])
	{
		str = ft_strjoin(data->env[i], data->cmd);
		if (access(str, F_OK) == 0)
			return (free(data->cmd), str);
		free(str);
		i++;
	}
	return (NULL);
}

void	ft_execve(t_pipex *pipex, char *argv, char **envp)
{
	char	**tmp;
	char	*path;

	tmp = ft_split(argv, ' ');
	if (!tmp)
	{
		printf("error split\n");
		exit(1);
	}
	path = cmd(pipex, tmp[0]);
	if (!path)
	{
		printf("command %s not found\n", tmp[0]);
		exit(127);
	}
	execve(path, tmp, envp);
}

void	ft_pipex(t_pipex *pipex, int i, char *argv, char **envp)
{
	if (pipe(pipex->fd) == -1)
		perror("pipe");
	pipex->pid = fork();
	if (pipex->pid == -1)
		perror("fork");
	if (pipex->pid == 0)
	{
		// redirection pipe
		if (i != 0)
			dup2(pipex->prev_fd, STDIN_FILENO);
		if (i != pipex->nb_cmd - 1)
			dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		if (file_redir(i, pipex))
		{
			ft_free(envp);
			free(argv);
			exit(1);
		}
		ft_execve(pipex, argv, envp);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->fd[1];
	// le parent doit toujours recuperer ce le l'enfant fait.
	close(pipex->fd[0]);
	// du coup on enregistre ce que le pipe 1 ecrit dans un fd temporaire.
	close(pipex->fd[1]);
}
