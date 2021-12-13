/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:12:09 by whazami           #+#    #+#             */
/*   Updated: 2021/12/03 18:28:21 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <curses.h>
# include "../libft/libft.h"

# define END_	25
# define ESPACE 26
# define INF_	29
# define SUP_	30
# define PIPE_	31

typedef enum OP { NONE, INF, DOUBLE_INF, SUP, DOUBLE_SUP }	t_op;

typedef struct s_redir
{
	t_op	op;
	char	*file;
}	t_redir;

typedef struct s_cmd
{
	char	*nom;
	char	*flag;
	char	**args;
	t_redir	**redirs;
}	t_cmd;

// ft_utils.c
void	free_2d_array(void **arr);
void	free_cmds(t_cmd **cmds);
void	print_cmds(t_cmd **cmd);
void	print_header(void);

/* parsing */
// ft_generate_new_line.c (manages quotes and $)
char	*generate_new_line(const char *line);
// ft_parse_cmds.c
t_cmd	**parsing(const char *line);
// ft_parse_combines.c
t_op	get_op(char *line, int *op_nbr);
// ft_parsing_err.c
int		parsing_error(char *line);
// ft_parse_utils.c
char	*ft_strchri(char *s, char c, int start, int stop);
void	erase_char(char *str, int index);
void	erase_str(char *str, int start, int nb_chars);
int		is_operator(char c);
void	replace_non_printables_in_str(char *str);
void	replace_non_printables(t_cmd *cmd);

#endif
