/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeyang <heeyang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:46:17 by heeyang           #+#    #+#             */
/*   Updated: 2021/03/16 08:45:22 by heeyang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct	s_data
{
	va_list	ap;
	int		num_return;
	int		i;
	int		zero;
	int		minus;
	int		width;
	int		prec;
	char	spec;
	int		idx_di;
}				t_data;

int				ft_printf(const char *format, ...);
void			read_format(t_data *data, char *format);
void			check_flag_spec(t_data *data, char *format);
void			init_data(t_data *data);
void			read_flag(t_data *data, char *format);
void			read_spec(t_data *data);

void			print_char(t_data *data);
void			print_str(t_data *data);
void			print_ptr(t_data *data);
void			print_di(t_data *data);
void			print_u(t_data *data);
void			print_x(t_data *data);

int				ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
char			*ft_strjoin(char *s1, char *s2);

#endif
