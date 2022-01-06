/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:12:09 by whazami           #+#    #+#             */
/*   Updated: 2022/01/06 12:20:11 by ytak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <term.h>
# include <curses.h>
# include <sys/errno.h>
# include "../libft/libft.h"

# define END_	25
# define ESPACE 26
# define INF	29
# define SUP	30
# define PIPE	31

int	g_exit_code;

typedef enum OP { NONE, IN, HEREDOC, OUT, APPEND }	t_op;

typedef struct s_redir
{
	t_op	op;
	char	*file;
}	t_redir;

typedef struct s_cmd
{
	char	*nom;
	char	**args;
	t_redir	**redirs;
	int		pid;
	int		exit;
}	t_cmd;

// ft_utils.c
void	free_2d_array(void **arr);
void	free_cmds(t_cmd **cmds);
int		is_empty(char *str);
int		print_err(char *cmd_name, char *error, char *error_parameter);
void	print_cmds(t_cmd **cmd);
void	print_header(void);

/* parsing */
// ft_generate_new_line.c (manages quotes, $ and non printables)
char	*generate_new_line(const char *line, char **env);
// ft_generate_nl_utils.c
char	*ft_strchri(char *s, char c, int start, int stop);
void	erase_char(char *str, int index);
char	get_non_printable(char c);
char	*ft_getenv(char *var_name, char **env);
// ft_parse_cmds.c
t_cmd	**parsing(const char *line, char **env);
// ft_parsing_err.c
int		err_combine_quotes(const char *line);
int		err_slash(const char *line);
int		err_semicolon(const char *line);
int		parsing_error(const char *line);
//ft_parse_chevrons.c
int		err_multiple_chevrons(const char *line);
int		err_chevrons_reverse(const char *line);
int		err_chevrons_space(const char *line);
//ft_parse_pipes.c
int		err_pipes(const char *line);
int		err_pipe_space(const char *line);
int		err_pipe_space_str(const char *line);
// ft_parse_utils.c
void	erase_str(char *str, int start, int nb_chars);
int		is_operator(char c);
t_op	get_op(char *line, int *op_nbr);

/* cmds */
// ft_cmds_echo_pwd.c
void	ft_echo(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd	*cmd, char **env);
void	ft_exit(t_cmd *cmd);
// ft_cmds_utils.c
void	non_built_in_command(t_cmd *cmd, char **env);
int		cmd_name_is(t_cmd *cmd, char *str);
int		is_built_in_cmd(t_cmd *cmd);
// ft_env_cmds.c
void	ft_env(char **env);
void	ft_unset(t_cmd *cmd, char **env);
void	ft_export(t_cmd *cmd, char ***env);
// ft_env_utils.c
void	init_env(char ***env);
int		get_var_id(char *var_name, char **env);
int		identifier_is_valid(char *identifier, int is_export);
void	print_sorted_env(char **env);
void	add_var_to_env(char *var, char ***env);
// ft_manage_cmds.c
void	manage_cmds(t_cmd **cmds, char ***env);
// ft_redirections.c
void	manage_heredocs(t_cmd **cmds);
int		manage_redirs(t_cmd *cmd);

#endif
