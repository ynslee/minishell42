/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:48:12 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/03 14:42:06 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_shlvl(t_env **env)
{
	t_node	*temp;
	int		shlvl;

	temp = get_value((*env)->vars, "SHLVL");
	shlvl = (int)ft_atoll(temp->value);
	free(temp->value);
	temp->value = ft_itoa(shlvl + 1);
}
