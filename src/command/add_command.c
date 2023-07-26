/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:42 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/26 10:23:10 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	*parse_input(char **input, int *index)
{
	int		str_len;
	int		cur_index;
	char	*str;
	int		space_count;

	space_count = -1;
	str_len = 0;
	cur_index = *index;
	if (ft_strchr_null("<|>", input[*index][0]))
		return (NULL);
	while ((*index) < ft_arrlen(input) && \
	!ft_strchr_null("<|>", input[*index][0]))
	{
		str_len += ft_strlen(input[*index]);
		(*index)++;
		space_count++;
	}
	str = ft_calloc((str_len + space_count + 1), sizeof(char));
	if (!str)
		printf("memory allocation error\n");
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	while (++cur_index < *index)
	{
		ft_strlcat(str, " ", str_len + space_count + 1);
		ft_strlcat(str, input[cur_index], str_len + space_count + 1);
	}
	return (str);
}

char	*parse_flags(char **input, int	*index)
{
	int	cur_index;

	cur_index = *index;
	if (input[*index][0] == '-')
	{
		(*index)++;
		return (input[cur_index]);
	}
	else
		return (NULL);
}

static char	*parse_redirection_input(char **input, int **index)
{
	int		str_len;
	int		cur_index;
	char	*str;

	str_len = 0;
	cur_index = **index;
	printf("parse_redirection_input cur_index %d\n", cur_index);
	if (ft_strchr_null("<|>", input[**index][0]))
		return (NULL);
	str_len += ft_strlen(input[**index]);
	(**index)++;
	str = ft_calloc((str_len + 1), sizeof(char));
	if (!str)
		printf("memory allocation fail\n");
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	return (str);
}

void	put_redirection(t_command *cmd, int *index, int track, char **input)
{
	char	*str;

	if (!ft_strncmp_all("<<", cmd[track].command))
	{
		str = parse_redirection_input(input, &index);
		put_to_input(cmd, track, str);
	}
	else
	{
		printf("in put_redirection\n");
		ft_print_array(input);
		str = parse_redirection_input(input, &index);
		strdup_filename(cmd, track, str);
	}
}

void	put_cmd_to_struct(t_command *cmd, \
					int struct_count, char **input)
{
	int		index;
	int		track;
	char	*str;

	index = 0;
	track = -1;
	printf("struct count: %i\n", struct_count);
	while (++track < struct_count)
	{
		if (ft_strchr("|", input[index][0]))
			index++;
		cmd[track].command = ft_strdup(input[index++]);
		if (!cmd[track].command)
			printf("strdup allocation fail!");
		if (ft_strchr("<>", cmd[track].command[0]))
			put_redirection(cmd, &index, track, input);
		else
		{
			if (!input[index])
				break ;
			str = parse_flags(input, &index);
			put_to_flags(cmd, track, str);
			if (!input[index])
				break ;
			str = parse_input(input, &index);
			put_to_input(cmd, track, str);
		}
	}
}
