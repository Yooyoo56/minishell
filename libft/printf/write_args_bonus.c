/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:37:58 by whazami           #+#    #+#             */
/*   Updated: 2021/07/30 18:38:04 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	get_int_len(int nb)
{
	int		len;
	long	nb_copy;

	len = 1;
	nb_copy = (long)nb;
	if (nb_copy < 0)
	{
		len++;
		nb_copy = -nb_copy;
	}
	while (nb_copy >= 10)
	{
		len++;
		nb_copy /= 10;
	}
	return (len);
}

static int	print_arg_or_get_its_len(va_list args, char c, int print, int sign)
{
	if (c == 'c')
		if (print)
			return (ft_putchar_fd(va_arg(args, int), 1));
	else
		return (1);
	else if (c == 's')
		if (print)
			return (ft_putstr_fd(va_arg(args, char *), 1));
	else
		return (ft_strlen(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_puthex((unsigned long)va_arg(args, void *), 0, 1, print));
	else if (c == 'd' || c == 'i')
		if (print)
			return (ft_putnbr_fd((long)sign * va_arg(args, int), 1));
	else
		return (get_int_len(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putuns(va_arg(args, unsigned int), print));
	else if (c == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 0, 0, print));
	else if (c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 1, 0, print));
	else
		return (ft_putchar_fd('%', 1));
}

static int	wid_min_dot_0(va_list a, va_list a_cp, const char *flag, char conv)
{
	int		arg_len;
	int		nb;
	int		len;
	int		is_neg;

	len = 0;
	arg_len = print_arg_or_get_its_len(a_cp, conv, 0, 1);
	va_end(a_cp);
	va_copy(a_cp, a);
	is_neg = ((conv == 'd' || conv == 'i') && (*flag == '0'
				|| *flag == '.') && va_arg(a_cp, int) < 0);
	if (is_neg)
		len += ft_putchar_fd('-', 1);
	va_end(a_cp);
	if (*flag == '-')
		len = print_arg_or_get_its_len(a, conv, 1, 1);
	nb = ft_atoi(flag + (*flag == '.' || *flag == '-'));
	while (nb-- > arg_len - is_neg * (*flag == '.'))
		if (*flag == '0' || *flag == '.')
			len += ft_putchar_fd('0', 1);
	else
		len += ft_putchar_fd(' ', 1);
	if (*flag == '-')
		return (len);
	return (len + print_arg_or_get_its_len(a, conv, 1, (is_neg * -2) + 1));
}

int	dot_flag_special_cases(va_list args, const char *flag_conv, char c)
{
	int		nb;
	char	*str;
	va_list	args_cp;

	nb = ft_atoi(flag_conv + 1);
	if (c == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			str = "(null)";
		if (nb > (int)ft_strlen(str))
			nb = (int)ft_strlen(str);
		write(1, str, nb);
		return (nb);
	}
	va_copy(args_cp, args);
	if ((c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X') && nb == 0
		&& va_arg(args_cp, int) == 0)
	{
		va_arg(args, int);
		va_end(args_cp);
		return (0);
	}
	va_end(args_cp);
	return (-1);
}

int	write_arg(va_list args, const char *flag_conv)
{
	int		last;
	int		ret;
	va_list	args_cp;

	last = ft_strlen(flag_conv) - 1;
	if (*flag_conv == '.')
	{
		ret = dot_flag_special_cases(args, flag_conv, flag_conv[last]);
		if (ret != -1)
			return (ret);
	}
	ret = 0;
	va_copy(args_cp, args);
	if (*flag_conv == '#' && flag_conv[last] == 'x' && va_arg(args_cp, int))
		ret += ft_putstr_fd("0x", 1);
	if (*flag_conv == '#' && flag_conv[last] == 'X' && va_arg(args_cp, int))
		ret += ft_putstr_fd("0X", 1);
	if ((*flag_conv == ' ' || *flag_conv == '+') && va_arg(args_cp, int) >= 0
		&& (flag_conv[last] == 'd' || flag_conv[last] == 'i'))
		ret += ft_putchar_fd(*flag_conv, 1);
	if (*flag_conv == '-' || *flag_conv == '.' || ft_isdigit(*flag_conv))
		return (wid_min_dot_0(args, args_cp, flag_conv, flag_conv[last]));
	va_end(args_cp);
	return (print_arg_or_get_its_len(args, flag_conv[last], 1, 1) + ret);
}
