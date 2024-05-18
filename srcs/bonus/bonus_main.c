/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 03:59:42 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/18 18:37:05 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_here_doc(t_pipex *pipex, char *lim)
{
	int		fd;
	char	*str;

	fd = open("here_doc",  O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (strerror(errno), exit(1));
	
	
}

void	init_data(t_pipex *data, int ac, char **av, char **envp)
{
	data->prev_fd = -1;
	data->outfile = av[ac - 1];
	data->nb_cmd = ac - 3;
	data->env = find_path(envp);
	data->pid = malloc(data->nb_cmd * sizeof(int));
	if (!data->pid)
		return (perror("malloc pid"), ft_free(data->env), exit(1));
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
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		ft_here_doc(&pipex, argv[2]);
	while (++i < pipex.nb_cmd)
		ft_pipex(&pipex, i, argv[i + 2], pipex.env);
	i = -1;
	while (++i < pipex.nb_cmd)
	{
		waitpid(pipex.pid[i], &pipex.status, 0);
		if (WIFEXITED(pipex.status))
			pipex.status = WEXITSTATUS(pipex.status);
	}
	close(pipex.fd[0]);
	return (free(pipex.pid), ft_free(pipex.env), pipex.status);
}
