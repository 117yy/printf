#include "printf.h"

void	put_per(t_va *va_data)
{
	int	len;
	int	len_blank;
	int	len_rest;

	if (va_data->blank == -1)
		va_data->blank = ' ';
	len = 1;
	len_rest = va_data->len - len;
	if (va_data->len < len)
		va_data->len = len;
	len_blank = va_data->width - va_data->len;
	if (va_data->sign != -1)
		put_blank(va_data->blank, len_blank);
	while (len_rest > 0)
	{
		len_rest--;
		write(1, &va_data->blank, 1);
	}
	write(1, "%", 1);
	if (va_data->sign == -1)
		put_blank(' ', len_blank);
	if (len_blank > 0)
		va_data->len += len_blank;
}
