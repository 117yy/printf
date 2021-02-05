#include "printf.h"

void			print(long arg, t_va *va_data, int len_blank, int len_rest)
{
	if (va_data->sign != -1)
		put_blank(va_data->blank, len_blank);
	if ((va_data->type == 'd' || va_data->type == 'u' || va_data->type == 'i')
			&& arg < 0)
	{
		write(1, "-", 1);
		arg *= -1;
	}
	put_blank('0', len_rest);
	if (va_data->len != 0 || arg != 0)
	{
		if (va_data->type == 'X')
			ori_putnbr_base(arg, "0123456789ABCDEF");
		else if (va_data->type == 'x')
			ori_putnbr_base(arg, "0123456789abcdef");
		else
			ori_putnbr_base(arg, "0123456789");
	}
	if (va_data->sign == -1)
		put_blank(' ', len_blank);
	if (len_blank > 0)
		va_data->len += len_blank;
}

static int		set_len(long arg, t_va *va_data, int len, int base)
{
	int	len_rest;

	if (va_data->blank == '0' && va_data->len == -1 &&
			va_data->len < va_data->width && va_data->sign != -1)
	{
		va_data->len = va_data->width;
		if (arg < 0)
			va_data->len--;
	}
	len_rest = va_data->len - len;
	if (va_data->len < len && (va_data->len != 0 || arg != 0))
		va_data->len = len;
	if (arg < 0 && base == 10)
		va_data->len++;
	return (len_rest);
}

void			put_number(t_va *va_data, long arg, int base)
{
	long	i;
	int		len;
	int		len_blank;
	int		len_rest;

	len = 1;
	i = 1;
	while (arg / (i *= base) != 0)
		len++;
	if (arg < 0 && base == 16)
		while (i < 2147483648)
		{
			len++;
			i *= base;
		}
	if (va_data->blank == -1 || va_data->len != -1)
		va_data->blank = ' ';
	len_rest = set_len(arg, va_data, len, base);
	len_blank = va_data->width - va_data->len;
	if (arg < 0 && base == 16)
		arg += i;
	print(arg, va_data, len_blank, len_rest);
}
