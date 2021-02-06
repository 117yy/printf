#include "ori_printf.h"

static int	is_over(long num, int minus, char next)
{
	if (num > LONG_MAX / 10)
	{
		if (minus == 1)
			return (0);
		else
			return (-1);
	}
	if (num == LONG_MAX / 10)
	{
		if (minus == 1)
		{
			if (next > '8')
				return (0);
		}
		else
		{
			if (next > '7')
				return (-1);
		}
	}
	return (1);
}

int			ori_atoi_count(const char *str, t_va *va_data)
{
	long	num;
	int		minus;
	int		i;
	int		bo;

	num = 0;
	minus = 0;
	i = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			minus++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		bo = is_over(num, minus, str[i]);
		if (bo != 1)
			return (bo);
		num *= 10;
		num += str[i++] - '0';
	}
	if (minus == 1)
		num *= -1;
	va_data->index += i;
	return ((int)num);
}
