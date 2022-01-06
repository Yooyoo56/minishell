/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:18:57 by ytak              #+#    #+#             */
/*   Updated: 2022/01/06 18:10:01 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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
}

void	cmd_signal(void)
{
	signal(SIGINT, interrupt_handler); // ctrl + c
//	signal(SIGQUIT, interrupt_handler); // ctrl + '\'
//	signal(SIGTERM, interrupt_handler); // ctrl + d
}

