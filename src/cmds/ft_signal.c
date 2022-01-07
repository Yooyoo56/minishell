/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:18:57 by ytak              #+#    #+#             */
/*   Updated: 2022/01/07 18:09:10 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
// first try = probleme
void	interrupt_handler(int sig)
{
	(void)sig;
	g_exit_code = 256;

//	write(STDERR_FILENO, "\b\b", 2);
	if (sig == SIGINT)
//    if (sig != SIGTERM)
	{
		write(STDERR_FILENO, "$>  \n ",5);
		write(STDERR_FILENO, "\b\b", 2);
//		write(STDERR_FILENO, "  \n", 3);
	}
	if (sig == SIGTERM)
		exit(0);
	else
	{
		write(STDOUT_FILENO, "$>   ", 5);
		write(STDERR_FILENO, "\b\b\b", 3);
	}
}
*/

// status : 자식 프로세스가 종료되면 자식 pid 값이 할당됨
// WNOHANG : 자식 프로세스가 종료되지 않아서 pid 값을 회수할수 없는 경우 반환값으로 0을 받음

void	handler_sigquit(int sig, pid_t pid)
{
	if (sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(STDOUT_FILENO, " \b\b", 4);
		}
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

/* ctrl + d (NOT a signal)= EOF
 * not working :(
 * */
void	cmd_eof(void)
{
	if (!EOF)
	{
		printf("exit\n");
		exit(0);
	}
}
