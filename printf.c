#include "printf.h"

void		va_init(t_va *va_data)
{
	va_data->type = 0;
	va_data->sign = 0;
	va_data->blank = -1;
	va_data->width = -1;
	va_data->len = -1;
	va_data->index = 1;
}

int			get_num(char *s, va_list args, t_va *va_data)
{
	int	n;

	n = 0;
	while (s[va_data->index] == '*')
	{
		n = va_arg(args, int);
		va_data->index++;
	}
	if ('0' <= s[va_data->index] && s[va_data->index] <= '9')
		n = ori_atoi_count(&s[va_data->index], va_data);
	while (s[va_data->index] == '*')
	{
		n = va_arg(args, int);
		va_data->index++;
	}
	return (n);
}

void		get_flag(char *s, va_list args, t_va *va_data)
{
	while (s[va_data->index] == '0' || s[va_data->index] == '-' ||
			s[va_data->index] == ' ')
	{
		s[va_data->index] == '-' ? va_data->sign = -1 : 0;
		s[va_data->index] == '0' ? va_data->blank = '0' : 0;
		s[va_data->index++] == ' ' ? write(1, " ", 1) : 0;
	}
	if (('0' <= s[va_data->index] && s[va_data->index] <= '9') ||
			s[va_data->index] == '*')
	{
		va_data->width = get_num(s, args, va_data);
		va_data->width < 0 ? va_data->sign = -1 : 0;
		va_data->width < 0 ? va_data->width *= -1 : 0;
	}
	if (s[va_data->index] == '.')
	{
		va_data->index++;
		va_data->len = get_num(s, args, va_data);
		va_data->len < 0 ? va_data->len = -1 : 0;
	}
	while (s[va_data->index] == '.' ||
			s[va_data->index] == '-' || s[va_data->index] == '0')
		va_data->index++;
}

void		put_va(char *s, va_list args, t_va *va_data)
{
	get_flag(s, args, va_data);
	va_data->type = s[va_data->index];
	if (s[va_data->index] == 'c')
		put_c(va_data, va_arg(args, int));
	else if (va_data->type == 's')
		put_s(va_data, va_arg(args, char *));
	else if (va_data->type == 'p')
		put_p(va_data, va_arg(args, long));
	else if (va_data->type == 'd' || s[va_data->index] == 'i')
		put_number(va_data, va_arg(args, int), 10);
	else if (va_data->type == 'u')
		put_number(va_data, va_arg(args, unsigned int), 10);
	else if (va_data->type == 'x')
		put_number(va_data, va_arg(args, int), 16);
	else if (va_data->type == 'X')
		put_number(va_data, va_arg(args, int), 16);
	else if (va_data->type == '%')
		put_per(va_data);
	else
		return ;
	va_data->index++;
}

int			ori_printf(const char *s, ...)
{
	va_list	args;
	int		len;
	int		count;
	t_va	va_data;

	va_start(args, s);
	len = 0;
	count = 0;
	while (s[len] != '\0')
		if (s[len] == '%')
		{
			va_init(&va_data);
			put_va((char *)&s[len], args, &va_data);
			count += va_data.len - va_data.index;
			len += va_data.index;
		}
		else
		{
			write(1, &s[len], 1);
			len++;
		}
	va_end(args);
	return (len + count);
}
