/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmameinert <emmameinert@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:39:58 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/27 12:45:40 by emmameinert      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

static void	sub_shlvl(t_env **env)
{
	t_node *temp;
	int shlvl;
	
	temp = get_value((*env)->vars, "SHLVL");
	shlvl = ft_atoi_exit(temp->value);	
	temp->value = ft_itoa(shlvl - 1);
}

void	execute_command(t_command *command, t_env **env)
{
	if (ft_strncmp_all(command->command, "env") == 0)
		ft_env(env);
	else if (ft_strncmp_all(command->command, "echo") == 0)
		ft_echo(command);
	else if (ft_strncmp_all(command->command, "cd") == 0)
		ft_cd(command, env);
	else if (ft_strncmp_all(command->command, "pwd") == 0)
		ft_pwd(*env);
	else if (ft_strncmp_all(command->command, "export") == 0)
		ft_export(command->input, *env);
	else if (ft_strncmp_all(command->command, "unset") == 0)
		ft_unset(command->input, *env);
	else if (ft_strncmp_all(command->command, "exit") == 0)
	{
		ft_exit(command);
		sub_shlvl(env);
		return ;
	}
	else if (ft_strncmp_all(command->command, "<<") == 0)
		ft_heredoc(command);
	else
		ft_execve(command, env);
	if (ft_strncmp_all(command->command, "./minishell") != 0)
		exit(0);
}

static int	dont_fork_cmd(t_command *command)
{
	if (ft_strncmp_all(command->command, "cd") == 0)
		return (1);
	else if (ft_strncmp_all(command->command, "export") == 0 && command->input)
		return (1);
	else if (ft_strncmp_all(command->command, "unset") == 0)
		return (1);
	else if (ft_strncmp_all(command->command, "exit") == 0)
		return (1);
	else
		return (0);
}

static int	execute_builtin(t_command *command, t_env **env)
{
	if (ft_strncmp_all(command->command, "env") == 0)
		ft_env(env);
	else if (ft_strncmp_all(command->command, "echo") == 0)
		ft_echo(command);
	else if (ft_strncmp_all(command->command, "cd") == 0)
		ft_cd(command, env);
	else if (ft_strncmp_all(command->command, "pwd") == 0)
		ft_pwd(*env);
	else if (ft_strncmp_all(command->command, "export") == 0)
		ft_export(command->input, *env);
	else if (ft_strncmp_all(command->command, "unset") == 0)
		ft_unset(command->input, *env);
	else if (ft_strncmp_all(command->command, "exit") == 0)
	{
		ft_exit(command);
		sub_shlvl(env);
		return (1);
	}
	else if (ft_strncmp_all(command->command, "<<") == 0)
		ft_heredoc(command);
	else 
		return (0);
	return (1);
}
static	int	one_command(t_command *command, int command_count, t_env **env)
{
	int			pid_test;
	
	pid_test = 0;
	if (command_count == 1)
	{
		if (dont_fork_cmd(command))
			execute_builtin(command, env);
		else
		{
			pid_test = fork();
			if (pid_test == 0)
				execute_command(command, env);
			waitpid(pid_test, NULL, 0);
			return (1);
		}
		return (1);
	}
	return (0);
}

int	execute_commands(t_command *commands, int command_count, t_env **env)
{
	int			i;
	int			pids[command_count];
	int			pipe_fds[(command_count * 2) - 2];

	i = -1;
	if (one_command(commands, command_count, env))
		return (0);
	while (++i < command_count)
	{
		commands->id = i;
		if (i != command_count - 1)
		{
			if (pipe(&pipe_fds[i * 2]) < 0)
				ft_putstr_fd("Piping error!", 2);
		}
		pids[i] = handle_pipe(commands, env, command_count, pipe_fds);
		commands++;
	}
	close_files(pipe_fds, command_count * 2 - 2);
	wait_children(pids, i - 1);
	return (0);
}
