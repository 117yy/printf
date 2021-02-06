#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "limits.h"

typedef struct	s_va
{
	char	type;
	int		sign;
	int		blank;
	int		width;
	int		len;
	int		index;
}				t_va;

int				ori_printf(const char *s, ...);
size_t	ori_strlen(const char *str);
int				ori_atoi_count(const char *str, t_va *va_data);
void			put_s(t_va *va_data, char *arg);
void			put_c(t_va *va_data, char arg);
void			put_p(t_va *va_data, long arg);
void			put_number(t_va *va_data, long arg, int base);
void			put_x(t_va *va_data, int arg);
void			put_per(t_va *va_data);
void			put_blank(char c, int n);
void			ori_putnbr_base(long nbr, char *base);
void			ori_putptr(long nbr, int len);

#endif
