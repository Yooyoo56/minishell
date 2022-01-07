/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:18:57 by ytak              #+#    #+#             */
/*   Updated: 2022/01/07 15:02:56 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*
void	child_pro_handler(int sig)
{
}

void interrupt_handler(int sig)
{
	if (// child /)
		return (child_pro_handler(sig);
	char *line;

	line = readline("$> ");
	// -1 : 자식 프로세스를 기다림
	// status : 자식 프로세스가 종료되면 자식 pid 값이 할당됨
	// WNOHANG : 자식 프로세스가 종료되지 않아서 pid 값을 회수할수 없는 경우 반환값으로 0을 받음
	if (sig == SIGINT)
	{
		line = readline("$> ");
	}
	else if (sig == SIGQUIT)
	{

	}
	exit(0);
}*/

/*
// first try
// probleme
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
	else if (sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(STDOUT_FILENO, "  \b\b", 4);
		}
		else
			write(STDOUT_FILENO, "QUIT: 3\n", 8);
	}
	else if (sig == SIGTERM)
	{
		write(STDIN_FILENO, "0", 1);
		exit(0);
	}
}

void	cmd_signal(void)
{
	signal(SIGINT, interrupt_handler); // ctrl + c
	signal(SIGQUIT, interrupt_handler); // ctrl + '\'
	signal(SIGTERM, interrupt_handler); // ctrl + d
}

