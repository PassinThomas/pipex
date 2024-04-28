/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:35:33 by tpassin           #+#    #+#             */
/*   Updated: 2024/04/28 21:28:11 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipex
{
    int     fd[2];
    int     pid;
    int     nb_cmd;
    int     fd_in;
    int     fd_out;
    int     prev_fd;
    char    *infile;
    char    *outfile;
    char    **cmd;
    char    **env_path;
}               t_pipex;

# endif