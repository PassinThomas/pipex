/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:59:42 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/24 21:00:23 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_here_doc(t_pipex *pipex, char *lim)
{
	int		fd;
	char	*str;

	pipex->here_doc = 1;
	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), exit(1));
	while (1)
	{
		ft_printf(1, "here_doc > ");
		str = get_next_line(0, 1);
		if (!str)
			break ;
		if (ft_strncmp(str, lim, ft_strlen(lim)) == 0
			&& str[ft_strlen(lim)] == '\n')
		{
			free(str);
			break ;
		}
		ft_printf(fd, "%s", str);
		free(str);
	}
	close(fd);
	pipex->infile = "here_doc";
}

void	init_data(t_pipex *data, int ac, char **av, char **envp)
{
	if (data->here_doc)
		data->nb_cmd = ac - 4;
	else
	{
		data->nb_cmd = ac - 3;
		data->infile = av[1];
	}
	data->prev_fd = -1;
	data->outfile = av[ac - 1];
	data->path = find_path(envp);
	data->pid = malloc(data->nb_cmd * sizeof(int));
	if (!data->pid)
		return (perror("malloc pid"), ft_free(data->path), exit(1));
}

char	**find_path(char **envp)
{
	char	*str;
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = -1;
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

int	ft_waitpid(t_pipex *pipex, int i)
{
	i = -1;
	while (++i < pipex->nb_cmd)
	{
		waitpid(pipex->pid[i], &pipex->status, 0);
		if (WIFEXITED(pipex->status))
			pipex->status = WEXITSTATUS(pipex->status);
	}
	return (pipex->status);
}

int	main(int argc, char *argv[], char **envp)
{
	int	i;

	t_pipex(pipex) = {0};
	i = -1;
	if (argc <= 5)
		return (ft_printf(2, "Error min 6 args\n"), 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc > 5)
		ft_here_doc(&pipex, argv[2]);
	init_data(&pipex, argc, argv, envp);
	while (++i < pipex.nb_cmd)
	{
		if (pipex.here_doc)
			ft_pipex(&pipex, i, argv[i + 3], envp);
		else
			ft_pipex(&pipex, i, argv[i + 2], envp);
	}
	pipex.status = ft_waitpid(&pipex, i);
	close(pipex.fd[0]);
	unlink("here_doc");
	return (free(pipex.pid), ft_free(pipex.path), pipex.status);
}
