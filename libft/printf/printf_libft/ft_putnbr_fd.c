/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:17:07 by whazami           #+#    #+#             */
/*   Updated: 2021/06/03 14:17:10 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(long int n, int fd)
{
	static int	len;
	static int	depth;
	int			len_copy;

	depth++;
	if (n >= 0 && n < 10)
		len += ft_putchar_fd(n + '0', fd);
	else if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	depth--;
	len_copy = len;
	if (depth == 0)
		len = 0;
	return (len_copy);
}
