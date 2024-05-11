/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:50:14 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/11 18:32:54 by tpassin          ###   ########.fr       */
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
	char	**tab;

	int(i) = 0;
	int(j) = -1;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tab = ft_split(envp[i] + 5, ':');
			while (tab[++j])
			{
				str = ft_strdup(tab[j]);
				free(tab[j]);
				tab[j] = ft_strjoin(str, "/");
				free(str);
			}
			return (tab);
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
	while (data->env[i])
	{
		str = ft_strjoin(data->env[i], command);
		if (access(str, F_OK) == 0 && access(str, X_OK) == 0 && access(str, R_OK) == 0)
			return (str);
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
		dprintf(2, "error split\n");
		exit(1);
	}
	if (ft_strchr(tmp[0], '/'))
	{
		dprintf(2, "%s\n", tmp[0]);
		if (access(tmp[0], F_OK) == 0 && access(tmp[0], X_OK) == 0 && access(tmp[0], R_OK) == 0)
			execve(tmp[0], tmp, envp);
		else if (access(tmp[0], F_OK) == 0 && (access(tmp[0], X_OK) || access(tmp[0], R_OK)))
		{
			dprintf(2, "permission denied: %s\n", tmp[0]);
			ft_free(tmp);
			ft_free(envp);
			exit(126);
		}
		else
		{
			dprintf(2, "no such file or directory: %s\n", tmp[0]);
			ft_free(tmp);
			ft_free(envp);
			exit(127);
		}
	}
	path = cmd(pipex, tmp[0]);
	if (!path)
	{
		dprintf(2, "command %s not found\n", tmp[0]);
		ft_free(tmp);
		ft_free(envp);
		exit(127);
	}
	execve(path, tmp, envp);
	perror("pipex");
	ft_free(tmp);
	ft_free(envp);
	exit(127);
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
			exit(1);
		}
		ft_execve(pipex, argv, envp);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->fd[0];
	// le parent doit toujours recuperer ce le l'enfant fait.
	// du coup on enregistre ce que le pipe 1 ecrit dans un fd temporaire.
	close(pipex->fd[1]);
}
