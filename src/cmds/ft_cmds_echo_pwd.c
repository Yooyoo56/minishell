/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_echo_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:48:02 by ytak              #+#    #+#             */
/*   Updated: 2022/01/04 15:24:59 by ytak             ###   ########.fr       */
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
			printf("cd: %s\n", str);
		}
	}
	//stat ==> il faut regarder
	// 1) gestion d'erreur : if directory doesn't exit
	// error :  No such file or directory
	else if (cmd->args[0])
	{
		chdir(cmd->args[0]);
		printf("cd dir:%s\n",cmd->args[0]);
	}
}

//gestion d'erreur
//1) exit  323 3232 ( if there is 2eme argument -> error); done
//2) exit 5454 (only the numbers can be here!!!)
//3) exit + espace 
//4) exit + 1rde (number + char)
//5) exit + ererer454 (char + number)
void	ft_exit(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->nom && cmd->args[0] == NULL)
	{
		cmd->exit = printf("exit\n");
		exit(0);
	}
	else if (cmd->nom  && cmd->args[1])
	{
		cmd->exit = printf("exit\n");
		print_err("exit", "too many arguments", NULL);
		exit(0);
	}
	else if (cmd->nom && (ft_atoi(cmd->args[0]) == ft_isalpha(ft_atoi(cmd->args[0]))))
	{
		cmd->exit = printf("exit\n");
		print_err("exit", "numeric argument required", NULL);
	}

	/*while(cmd->args[0][i])
	{
		if ((ft_atoi(cmd->args[0]) == ft_isdigit(ft_atoi(&cmd->args[0][i]))))
		{
			cmd->exit = printf("exit\n");
			print_err("exit", "numeric argument required", NULL);
			i++;
	//		exit(0);
		}
		i++;
	}*/

}
