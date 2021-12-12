/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 03:55:05 by whazami           #+#    #+#             */
/*   Updated: 2021/09/10 23:41:50 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "printf_libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	write_arg(va_list args, const char *flag_conv);
int	ft_putuns(unsigned int n, int print);
int	ft_puthex(unsigned long nbr, int maj, int Ox, int print);

#endif
