/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:26:21 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/28 15:22:20 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

void	ft_dup2(int infile_fd, int outfile_fd)
{
	if (infile_fd != -2 && dup2(infile_fd, 0) < 0)
		ft_putstr_fd("infile_fd:  Dup 2 error!\n", 2);
	if (outfile_fd != -2 && dup2(outfile_fd, 1) < 0)
		ft_putstr_fd("outfile_fd: Dup 2 error!\n", 2);
}

void	redirect_io(int infile_fd, int outfile_fd)
{
	ft_dup2(infile_fd, outfile_fd);
}

void	redirect_files(t_command *current)
{
	int	fd;

	fd = -2;
	printf("should_open_files?\n");
	if (current->token == INPUT)
	{
		fd = open_file(current->infile_name, O_RDONLY);
		g_info.fds[current->id * 2] = fd;
		ft_dup2(g_info.fds[current->id * 2], -2);
	}
	else if (current->token == OUTPUT_TRUNC)
	{
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_TRUNC);
		g_info.fds[current->id * 2 + 1] = fd;
		ft_dup2(-2, g_info.fds[current->id * 2 + 1]);
	}
	else if (current->token == OUTPUT_APPEND)
	{
		fd = open_file(current->outfile_name, O_CREAT | O_WRONLY | O_APPEND);
		g_info.fds[current->id * 2 + 1] = fd;
		ft_dup2(-2, g_info.fds[current->id * 2 + 1]);
	}
}

int	parse_redirection(t_command *cmd, int track, char *str, char *input)
{
	printf("open_redir: str is %s\n", str);
	printf("open_redir: input is %s\n", input);
	if (!ft_strncmp_all("<", input))
	{
		cmd[track].infile_name = ft_strdup(str);
		if (!cmd[track].infile_name)
			printf("strdup allocation fail!\n");
		cmd[track].token = INPUT;
	}
	else if (!ft_strncmp_all(">", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail!\n");
		cmd[track].token = OUTPUT_TRUNC;
	}
	else if (!ft_strncmp_all(">>", input))
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail!\n");
		cmd[track].token = OUTPUT_APPEND;
	}
	return (0);
}
