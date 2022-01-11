/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:18:57 by ytak              #+#    #+#             */
/*   Updated: 2022/01/10 14:51:04 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handler_sigquit(int sig, pid_t pid)
{
	if (sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(STDOUT_FILENO, "  \b\b", 4);
		}
		else
			write(STDOUT_FILENO, "Quit: 3\n", 8);
	}
}

void	interrupt_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(STDOUT_FILENO, "  \n", 3);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(STDOUT_FILENO, "  \n", 3);
	}
	handler_sigquit(sig, pid);
}

/* SIGINT = ctrl + c
 * SIGQUIT = ctrl +  \
 * */
void	cmd_signal(void)
{
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
}
