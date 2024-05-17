/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:50:14 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/17 18:42:12 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exit(int code, char **envp, char **tmp)
{
	ft_free(envp);
	if (code == 1)
		return (ft_printf(2, "error split\n"), ft_free(tmp), exit(1));
	else if (code == 2)
	{
		ft_printf(2, "permission denied: %s\n", tmp[0]);
		return (ft_free(tmp), exit(126));
	}
	else if (code == 3)
	{
		ft_printf(2, "no such file or directory: %s\n", tmp[0]);
		return (ft_free(tmp), exit(127));
	}
	else if (code == 4)
	{
		ft_printf(2, "command %s not found\n", tmp[0]);
		return (ft_free(tmp), exit(127));
	}
	else if (code == 5)
	{
		perror("pipex");
		return (ft_free(tmp), exit(126));
	}
}

char	*cmd(t_pipex *data, char *command)
{
	char	*str;
	int		i;

	i = 0;
	while (data->env[i])
	{
		str = ft_strjoin(data->env[i], command);
		if (access(str, F_OK | X_OK | R_OK) == 0)
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
	if (!tmp || !*tmp)
		ft_exit(1, envp, tmp);
	if (ft_strchr(tmp[0], '/'))
	{
		if (access(tmp[0], F_OK | X_OK | R_OK) == 0)
			execve(tmp[0], tmp, envp);
		else if (access(tmp[0], F_OK) == 0 && (access(tmp[0], X_OK | R_OK)))
			ft_exit(2, envp, tmp);
		else
			ft_exit(3, envp, tmp);
	}
	path = cmd(pipex, tmp[0]);
	if (!path)
		ft_exit(4, envp, tmp);
	execve(path, tmp, envp);
	ft_exit(5, envp, tmp);
}

int	file_redir(int i, t_pipex *pipex)
{
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

void	ft_pipex(t_pipex *pipex, int i, char *argv, char **envp)
{
	if (pipe(pipex->fd) == -1)
		perror("pipe");
	pipex->pid[i] = fork();
	if (pipex->pid[i] == -1)
		perror("fork");
	if (pipex->pid[i] == 0)
	{
		free(pipex->pid);
		if (i != 0)
			dup2(pipex->prev_fd, STDIN_FILENO);
		if (i != pipex->nb_cmd - 1)
			dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		if (pipex->prev_fd > 2)
			close(pipex->prev_fd);
		if (file_redir(i, pipex))
			return (ft_free(envp), exit(1));
		ft_execve(pipex, argv, envp);
	}
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	close(pipex->fd[1]);
	pipex->prev_fd = pipex->fd[0];
}
