/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:45:34 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/15 03:13:20 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_spec(t_data *data)
{
	if (data->spec == '%')
		print_char(data);
	else if (data->spec == 'c')
		print_char(data);
	else if (data->spec == 's')
		print_str(data);
	else if (data->spec == 'p')
		print_ptr(data);
	else if (data->spec == 'd' || data->spec == 'i')
		print_di(data);
	else if (data->spec == 'u')
		print_u(data);
	else if (data->spec == 'x' || data->spec == 'X')
		print_x(data);
}

void	read_flag(t_data *data, char *format)
{
	if (format[data->i] == '0' && data->width == 0 && data->prec == -1)
		data->zero = 1;
	else if (format[data->i] == '-')
		data->minus = 1;
	else if (format[data->i] == ' ')
		data->idx_di = 3;
	else if (format[data->i] == '.')
		data->prec = 0;
	else if (format[data->i] == '*' && data->prec == -1)
	{
		if ((data->width = va_arg(data->ap, int)) < 0)
		{
			data->minus = 1;
			data->width *= -1;
		}
	}
	else if (format[data->i] == '*')
		data->prec = va_arg(data->ap, int);
	else if (ft_strchr("0123456789", format[data->i]) && data->prec == -1)
		data->width = data->width * 10 + format[data->i] - 48;
	else if (ft_strchr("0123456789", format[data->i]))
		data->prec = data->prec * 10 + format[data->i] - 48;
}

void	check_flag_spec(t_data *data, char *format)
{
	data->i++;
	while (format[data->i] && !(ft_strchr("cspdiuxX%", format[data->i])))
	{
		read_flag(data, format);
		data->i++;
	}
	data->spec = format[data->i];
	if (data->spec != '%')
	{
		if (data->minus == 1)
			data->zero = 0;
		if (data->prec > -1)
			data->zero = 0;
	}
	read_spec(data);
}

void	read_format(t_data *data, char *format)
{
	while (format[data->i] != '\0')
	{
		if (format[data->i] == '%')
		{
			init_data(data);
			check_flag_spec(data, format);
		}
		else
			data->num_return += ft_putchar_fd(format[data->i], 1);
		data->i++;
	}
}

int		ft_printf(const char *format, ...)
{
	int		ret;
	t_data	*data;

	if (!(data = malloc(sizeof(t_data) * 1)))
		return (-1);
	data->num_return = 0;
	data->i = 0;
	va_start(data->ap, format);
	read_format(data, (char *)format);
	va_end(data->ap);
	ret = data->num_return;
	free(data);
	return (ret);
}
