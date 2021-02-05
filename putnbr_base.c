#include <unistd.h>
#include "printf.h"

int		ori_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int		can_work(int len, char *base)
{
	int i;
	int j;

	i = 0;
	while (i < len)
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (j < len)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ori_putnbr(long nbr)
{
	int		len;
	int		nbr_base[35];
	int		i;
	long	nbr_long;

	nbr_long = nbr;
	len = 10;
	if (nbr_long < 0)
	{
		write(1, "-", 1);
		nbr_long *= -1;
	}
	if (nbr_long == 0)
		write(1, "0", 1);
	i = 0;
	while (nbr_long != 0)
	{
		nbr_long /= len;
		i++;
	}
	while (--i >= 0)
		write(1, &nbr_base[i], 1);
}

void	ori_putnbr_base(long nbr, char *base)
{
	int		len;
	int		nbr_base[35];
	int		i;
	long	nbr_long;

	nbr_long = nbr;
	len = ori_strlen(base);
	if (nbr_long == 0)
		write(1, "0", 1);
	i = 0;
	while (nbr_long != 0)
	{
		nbr_base[i] = base[nbr_long % len];
		nbr_long /= len;
		i++;
	}
	while (--i >= 0)
		write(1, &nbr_base[i], 1);
}

void	ori_putptr(long ptr, int len)
{
	int		ptr_16_base[50];
	int		i;
	char	*base;

	base = "0123456789abcdef";
	i = 0;
	while (ptr != 0)
	{
		ptr_16_base[i] = base[ptr % 16];
		ptr /= 16;
		i++;
	}
	while (i < len)
	{
		ptr_16_base[i] = '0';
		i++;
	}
	while (--i >= 0)
		write(1, &ptr_16_base[i], 1);
}
