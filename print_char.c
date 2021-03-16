/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:54:25 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/14 10:06:07 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_width(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->width)
	{
		if (data->zero == 1)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		i++;
		data->num_return++;
	}
}

void		print_char(t_data *data)
{
	int	c;

	if (data->spec == '%')
		c = '%';
	else
	{
		c = va_arg(data->ap, int);
		data->zero = 0;
	}
	if (data->spec == '%' && data->minus == 1)
		data->zero = 0;
	if (data->minus == 1)
	{
		ft_putchar_fd(c, 1);
		print_width(data);
		data->num_return++;
	}
	else
	{
		print_width(data);
		ft_putchar_fd(c, 1);
		data->num_return++;
	}
}
