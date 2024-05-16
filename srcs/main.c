/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:59:42 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:32:33 by tpassin          ###   ########.fr       */
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

void	ft_waitpid(t_pipex pipex, int i, int status)
{
	i = -1;
	while (++i < pipex.nb_cmd)
	{
		waitpid(pipex.pid[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	(pipex) = {0};

	int(i) = -1;
	if (argc < 5 || !*envp)
		return (1);
	init_data(&pipex, argc, argv);
	pipex.env = find_path(envp);
	pipex.pid = malloc(pipex.nb_cmd * sizeof(int));
	if (!pipex.pid)
		return (perror("malloc pid"), ft_free(pipex.env), 1);
	while (++i < pipex.nb_cmd)
		ft_pipex(&pipex, i, argv[i + 2], pipex.env);
	ft_waitpid(pipex, i, pipex.status);
	close(pipex.fd[0]);
	return (free(pipex.pid), ft_free(pipex.env), pipex.status);
}
