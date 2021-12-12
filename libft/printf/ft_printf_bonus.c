/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:45:56 by whazami           #+#    #+#             */
/*   Updated: 2021/08/03 19:42:14 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*my_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (!*s)
			return ((char *)s + ft_strlen(s));
		s++;
	}
}

int	ft_putuns(unsigned int n, int print)
{
	static int	len;
	static int	depth;
	int			len_copy;

	depth++;
	if (n < 10)
	{
		if (print)
			len += ft_putchar_fd(n + '0', 1);
		else
			len++;
	}
	else
	{
		ft_putuns(n / 10, print);
		ft_putuns(n % 10, print);
	}
	depth--;
	len_copy = len;
	if (depth == 0)
		len = 0;
	return (len_copy);
}

int	ft_puthex(unsigned long nbr, int maj, int Ox, int print)
{
	int				i;
	int				ibase;
	int				len_nbr;
	char			*base;

	if (Ox && print)
		ft_putstr_fd("0x", 1);
	base = "0123456789abcdef";
	if (maj)
		base = "0123456789ABCDEF";
	len_nbr = 1;
	while (nbr / power(16, len_nbr) >= 16)
		len_nbr++;
	len_nbr += (nbr >= 16);
	i = -1;
	while (i++ < len_nbr - 1)
	{
		ibase = nbr / power(16, len_nbr - i - 1);
		nbr -= ibase * power(16, len_nbr - i - 1);
		if (print)
			ft_putchar_fd(base[ibase], 1);
	}
	return (len_nbr + Ox * 2);
}

static char	*get_prct_str(const char *pos_prct)
{
	char	*prct_str;
	int		len;

	len = 1;
	while (ft_isdigit(pos_prct[len]) || pos_prct[len] == '-'
		|| pos_prct[len] == '.' || pos_prct[len] == '#'
		|| pos_prct[len] == ' ' || pos_prct[len] == '+')
		len++;
	len++;
	prct_str = (char *)malloc(len + 1);
	if (!prct_str)
		return (NULL);
	ft_strlcpy(prct_str, pos_prct, len + 1);
	return (prct_str);
}

int	ft_printf(const char *str, ...)
{
	char	*pos_prct;
	char	*future_pos_prct;
	int		tot_len_arg;
	char	*prct_str;
	va_list	args;

	pos_prct = my_strchr(str, '%');
	write(1, str, pos_prct - str);
	tot_len_arg = 0;
	va_start(args, str);
	while (pos_prct != str + ft_strlen(str))
	{
		prct_str = get_prct_str(pos_prct);
		tot_len_arg += write_arg(args, prct_str + 1) - ft_strlen(prct_str);
		future_pos_prct = my_strchr(pos_prct + ft_strlen(prct_str), '%');
		write(1, pos_prct + ft_strlen(prct_str),
			(future_pos_prct - str) - (pos_prct - str) - ft_strlen(prct_str));
		pos_prct = future_pos_prct;
		free(prct_str);
	}
	va_end(args);
	return (ft_strlen(str) + tot_len_arg);
}
