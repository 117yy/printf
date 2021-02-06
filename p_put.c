#include "ori_printf.h"

static int		set_len(t_va *va_data, long arg)
{
	int		len;
	long	i;

	va_data->blank == -1 ? va_data->blank = ' ' : 0;
	len = 3;
	i = 1;
	while (arg / (i *= 16) != 0)
		len++;
	len < va_data->len ? len = va_data->len : 0;
	len == 9 ? len += 2 : 0;
	if (arg == 0 && va_data->len == 0)
		len = 2;
	else if (arg == 0)
		len = va_data->len + 4;
	return (len);
}

void			put_p(t_va *va_data, long arg)
{
	int		len;
	int		len_blank;

	len = set_len(va_data, arg);
	len_blank = va_data->width - len;
	va_data->sign == -1 ? 0 : put_blank(' ', len_blank);
	write(1, "0x", 2);
	if (arg == 0 && va_data->len != 0)
	{
		write(1, "0", 1);
		put_blank('0', va_data->len - 1);
	}
	if (arg != 0)
	{
		if (len == 11 && va_data->len >= 9)
			va_data->len == 9 ? write(1, "0", 1) : write(1, "1", 1);
		ori_putptr(arg, len - 3);
	}
	va_data->sign == -1 ? put_blank(' ', len_blank) : NULL;
	len_blank > 0 ? len += len_blank : 0;
	if (!arg && va_data->len > 0)
		len -= 2;
	va_data->len = len;
}
