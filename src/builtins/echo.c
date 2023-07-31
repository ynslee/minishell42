/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:25:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/31 09:20:30 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

/*
-takes in an array of strings, each index is a string from the command line.
-if the first string is "-n" echo adds a newline at the end of the last string.
-echo returns 0 if successfull and 1 if not.
*/

void	ft_echo(t_command *command)
{
	int	new_line;

	new_line = 0;
	if (command->flags)
	{
		if (ft_strncmp_all(command->flags, "-n") == 0)
			new_line = 1;
		else
		{
			ft_putstr_fd(command->flags, 1);
			ft_putchar_fd(' ', 1);
		}
	}
	ft_putstr_fd(command->input, 1);
	if (new_line == 0)
		ft_putchar_fd('\n', 1);
}
