/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:48:02 by ytak              #+#    #+#             */
/*   Updated: 2022/01/05 18:50:18 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	there_is_only_char_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 0;
	while (cmd->args[i] != NULL && cmd->args[i][0] == '-'
		&& there_is_only_char_in_str('n', cmd->args[i] + 1))
	{
		flag_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag_n)
		printf("\n");
}

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	if (errno == ERANGE)
	{
		printf("pwd: error retrieving curremt directory");
		printf(":getcwd: cannot access parent directories");
		printf(": No such file or directory\n");
	}
	else
		printf("%s\n", buf);
}

void ft_cd(t_cmd *cmd, char **env)
{
	char *str;
	int i = 0;

	str = ft_getenv("HOME", env);
	if (cmd->nom && cmd->args[0] == NULL)
	{
		if (str[0] == '\0')
		{
			print_err("cd", "HOME not set", NULL);
			cmd->exit = 1;
		}
		else
		{
			chdir(str);
//			printf("cd: %s\n", str);
		}
	}
	while(cmd->args[i])
	{
		if (cmd->args[0][i] == '~')
		{
			if (cmd->args[0][i + 1] == '~')
			{
				print_err("cd", "No such file or directory", NULL);
			}
			chdir(str);
		}
		else if (chdir(cmd->args[0])== -1)
			print_err("cd", "No such file or directory", NULL);
		i++;
	}

/*	while (cmd->args[i])
	{
		if (chdir(cmd->args[0]) == -1)
		{
			print_err("cd", "No such file or directory", NULL);
		}
//		chdir(cmd->args[i]);
		i++;
	}*/

/*
	// 1) gestion d'erreur : if directory doesn't exit
	while (cmd->args[0])
	{
		if (chdir(cmd->args[0]) == -1)
	//		printf("bash: cd: %s: No such file or directory\n",cmd->args[0]);
			print_err("cd", "No such file or directory", NULL);
		chdir(cmd->args[0]);
		//printf("cd dir:%s\n",cmd->args[0]);
	} */
}

//gestion d'erreur
//1) exit  323 3232 ( if there is 2eme argument -> error); done
//2) exit 5454 (only the numbers can be here!!!)
//3) exit + espace 
//4) exit + 1rr1 (number + char)
//5) exit + ererer454 (char + number)
void	ft_exit(t_cmd *cmd)
{
	int i;

	i = 0;
//	while (cmd->args[i])  //=> can't detect 1r
//	while (cmd->args[0][i])  // -> exit espace (seg fault)
	while (cmd->nom && cmd->args[0][i]) // ->exit space  (seg fault, whyyy)
	{
			if((cmd->args[0][i] >= 'a' && cmd->args[0][i] <= 'z') || (cmd->args[0][i]>= 'A' && cmd->args[0][i] <= 'Z'))
			{
				cmd->exit = printf("exit\n");
				print_err("exit", "numeric argument required", NULL);
				exit(0);
			}
			i++;
	}
	if (cmd->nom && cmd->args[0] == '\0')
	{
		cmd->exit = printf("exit\n");
		exit(0);
	}
	else if (cmd->nom && cmd->args[0] && cmd->args[1])
	{
		cmd->exit = printf("exit\n");
		print_err("exit", "too many arguments", NULL);
		exit(0);
	}
}

