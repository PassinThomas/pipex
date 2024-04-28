/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:50:14 by tpassin           #+#    #+#             */
/*   Updated: 2024/04/28 22:02:26 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_data(int ac, char **av, char **envp, t_pipex *data)
{
    data->prev_fd = -1;
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->env = envp;
	data->cmd = &av[2];
	data->nb_cmd = ac - 3;
    data->fd_in = open("blabla");
    data->fd_out = open("blablabla");
}

char	**find_path(char **envp)
{
	char	*str;
	char	**split;

	int (i) = 0;
	int (j) = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			split = ft_split(envp[i] + 5);
			while (split[j++])
			{
				str = ft_strdup(split[j])
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

char    *cmd(t_pipex *data, int i, char **envp, char *command)
{
    if (ft_strchr(command, '/'))
    {
       char tmp = ft_strdup(command);
        return (tmp);
    }
	data->cmd = find_path(envp);
    char *str;
	int i = 0;
    while (data.cmd[i])
    {
        str = ft_strjoin(split[i], command);
	    if (access(str, F_OK) == 0)
	    {
	    	return (str)
	    }
        free(str);
        i++;
    }
    return (NULL);
}

int ft_pipex(t_pipex *pipex, int i, char *argv, char **envp)
{
    if (pipe(pipex->fd) == -1)
        return (printf("error"));
    pipex->pid = fork()
    if (pid == -1)
        return (printf("error"));
    if (pid == 0)
    {
        if (i != 0)
            dup2(pipex->prev_fd, STDIN_FILENO);
        if (i != pipex->nb_cmd - 1)
            dup2(pipex.fd[1], STDOUT_FILENO);
        close(pipex.fd[0]);
        close(pipex.fd[1]);
        if (i == 0)
        {
            if (pipex->fd_in < 0)
                return ("error");
            dup2(pipex->fd_in, STDIN_FILENO);
            close()
        }
        if (i == pipex->nb_cmd - 1)
        {
            if (pipex->fd_out < 0)
                return ("error");
            dup2(pipex->fd_out, STDOUT_FILENO);
            close();
        }
        ft_execve(pipex, argv, envp);
    }
    else
    {
        if (pipex->prev_fd != -1)
            close(pipex->prev_fd);
        pipex->prev_fd = pipex->fd[1]; // le parent doit toujours recuperer ce le l'enfant fait.
        close(pipex->fd[0]);// du coup on enregistre ce que le pipe 1 ecrit dans un fd temporaire.
        close(pipex.fd[1]);
    }
}

void ft_execve(t_pipex *pipex, char *argv, char **envp)
{
    **tmp = split(argv, ' ');
    if (!tmp)
        "error";
    path = cmd(pipex, tmp[0]);
    if (!path)
        "error";
    execve(path, tmp, envp);
}

int main(int argc, char const *argv[], char **envp)
{
    argv = "ls -la" 
    path = "/bin/ls"
    //execve veut path, [ls][la]
    t_pipex pipex;

    pipex = NULL;
    pipex.env_path = find_path(envp);
    int = 1;

    while (i < pipex.nb_cmd)
    {
        ft_pipex(&pipex, i, argv[i], envp);
        i++;
    }
    while (wait(NULL) > 0)
        ;
    return 0;
}
