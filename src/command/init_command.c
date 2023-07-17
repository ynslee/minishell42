/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/17 09:32:44 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"

//here it <<, >> case should be added.
static int count_struct(char **input, int struct_count)
{
	int index;

	index = 0;
	while (input[index])
	{
		if ((ft_strchr("<|>", input[index][0])) || index == 0)
		{
			struct_count++;
			index++;
		}
		else
			index++;
	}
	return (struct_count);
}

static char *put_to_input(char **input, int *index)
{
	int		str_len;
	int		cur_index;
	char	*str;
	int		space_count = -1;

	str_len = 0;
	cur_index = *index;
	while (input[*index] != NULL && !ft_strchr("<|>",input[*index][0]))
	{
		str_len += ft_strlen(input[*index]);
		(*index)++;
		space_count++;
	}
	str = malloc(sizeof(char) * (str_len + space_count + 1));
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	printf("str after strlcpy is now %s|\n", str);
	while (++cur_index < *index)
	{
		ft_strlcat(str, " ", str_len + space_count + 1);
		printf("str after first strlcat is now %s|\n", str);
		ft_strlcat(str, input[cur_index], str_len + space_count + 1);
		printf("str after second strlcat is now %s|\n", str);
	}
	return (str);
}

static char	*put_to_flags(char **input, int	*index)
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

static t_command *put_cmd_to_struct(t_command *cmd, int index, int struct_count, char **input)
{
	int track;
	char	*str;

	track = -1;
	printf("here1\n");
	while (++track < struct_count)
	{
		printf("index is %d\n", index);
		if (ft_strchr("|", input[index][0]))
			index++;
		cmd[track].command = ft_strdup(input[index++]);
		printf("here2\n");
		cmd[track].flags = put_to_flags(input, &index);
		printf("here3\n");
		str = put_to_input(input, &index);
		cmd[track].input = ft_strdup(str);
		free(str);
		printf("here4\n");
	}
	cmd[struct_count + 1].command = NULL;
	return (cmd);
}

t_command	*init_cmds(t_command *cmd, char **input)
{
	int	index;
	int	struct_count;

	index = 0;
	struct_count = 0;
	struct_count = count_struct(input, struct_count);
	printf("struct count is %d\n", struct_count);
	cmd = ft_calloc(struct_count + 1, sizeof(t_command));
	cmd = put_cmd_to_struct(cmd, index, struct_count, input);
	/*
	int	i = 0;
	while (cmd[i].command)
	{
		printf("before main Command: %s\n", cmd[i].command);
		printf("before main flags: %s\n",cmd[i].flags);
		printf("before main input: %s\n", cmd[i].input);
		i++;
	}
	*/
	//This to remain that it is funny that for some reason the char*flags in the struct 
	//is not assign to null;it got segfault when I try to printf it out, just only that, we can printf
	//the other thing without problem. could be memory allocate by using ft_calloc
	//but we just need our command = null then we stop extract thing to do in minishell.
	//printf("second Command: %s\n", cmd[1].command);
	//printf("second flags: %s\n",cmd[1].flags);
	//printf("second input: %s\n", cmd[1].input);
	return (cmd);
}
