/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:11:37 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/18 10:07:35 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	update_command_redir(t_command *command)
{
	int	fd;

	if (command->infile_name && !ft_strncmp(command->infile_name, "HEREDOC", 7))
	{
		fd = open_file(command->infile_name, O_RDONLY);
		command->token = INPUT;
		command->redir_fd_index_in = g_info.redir_index_count;
		g_info.redir_fds[g_info.redir_index_count++] = fd;
		unlink(command->infile_name);
	}
}

static int	check_for_cat_grep(char *str)
{
	if (!ft_strncmp_all("cat", str) || !ft_strncmp_all("grep", str) \
		|| !ft_strncmp_all("wc", str))
		return (1);
	return (0);
}

static int	check_index_for_pipes(int *index, char **input)
{
	int		cmd_index;

	cmd_index = 0;
	if ((*index) > 0 && input[(*index) - 1] \
		&& input[(*index) - 1][0] != '|')
		cmd_index = (*index) - 1;
	else if (input[(*index) + 1] && input[(*index) + 2] \
		&& input[(*index) + 2][0] != '|')
		cmd_index = (*index) + 2;
	return (cmd_index);
}

int	handle_heredoc(t_command *cmd, int *index, int track, char **input)
{
	int		cmd_index;
	char	*file_name;
	char	*number;

	number = ft_itoa(track);
	file_name = ft_strjoin("HEREDOC", number);
	free(number);
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		cmd_index = check_index_for_pipes(index, input);
		if (check_for_cat_grep(input[cmd_index]) || \
			(input[cmd_index][0] == '-' && ft_isalpha(input[cmd_index][1])))
			cmd[track].infile_name = ft_strdup(file_name);
		if (cmd[track].infile_name && \
			ft_strncmp(cmd[track].infile_name, "HEREDOC", 7))
		{
			update_infile_redir_heredoc(cmd, track);
			cmd[track].infile_name = ft_strdup(file_name);
		}
		free(file_name);
		(*index) += 2;
		return (1);
	}
	free(file_name);
	return (0);
}
