/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:59:42 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/22 17:20:47 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_data(t_pipex *data, int ac, char **av, char **envp)
{
	data->prev_fd = -1;
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->nb_cmd = ac - 3;
	data->path = find_path(envp);
	data->pid = malloc(data->nb_cmd * sizeof(int));
	if (!data->pid)
		return (perror("malloc pid"), ft_free(data->path), exit(1));
}

char	**find_path(char **envp)
{
	char	*str;
	char	**tab;

	int (i) = 0;
	int (j) = -1;
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

int	main(int argc, char *argv[], char **envp)
{
	t_pipex(pipex) = {0};
	int (i) = -1;
	if (argc < 5)
		return (1);
	init_data(&pipex, argc, argv, envp);
	while (++i < pipex.nb_cmd)
		ft_pipex(&pipex, i, argv[i + 2], envp);
	i = -1;
	while (++i < pipex.nb_cmd)
	{
		waitpid(pipex.pid[i], &pipex.status, 0);
		if (WIFEXITED(pipex.status))
			pipex.status = WEXITSTATUS(pipex.status);
	}
	close(pipex.fd[0]);
	return (free(pipex.pid), ft_free(pipex.path), pipex.status);
}
