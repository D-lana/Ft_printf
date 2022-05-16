#include "ft_printf.h"

long long int	ft_number_size(va_list argument, t_list flags, int *zero)
{
	long long int	d;

	if (flags.lh == 5)
		d = va_arg(argument, long int);
	if (flags.lh == 6)
		d = va_arg(argument, long long int);
	if (d == LLONG_MIN || d == LONG_MIN)
		*zero = 2;
	if (flags.lh != 5 && flags.lh != 6)
	{
		d = va_arg(argument, int);
		if (flags.lh == 7)
			d = (short int) d;
		if (flags.lh == 8)
			d = (char) d;
	}
	return (d);
}

static t_list	ft_nbrlen(int *len, long long int nb, t_list flags, int *zero)
{
	int	i;

	i = 0;
	*len = 0;
	if (*zero == 2)
	{
		*len = 20;
		return (flags);
	}
	if (nb == 0 && flags.point != -1)
		return (flags);
	if (nb < 0)
	{
		flags.minus = 1;
		nb = -nb;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	i++;
	*len = i;
	return (flags);
}

static int	ft_long_min(int *zero)
{
	if (*zero == 2)
	{
		write(1, "-9223372036854775808", 20);
		return (1);
	}
	return (0);
}

static void	ft_putnbr_printf(long long int nb, t_list flags, int *zero)
{
	if (ft_long_min(&*zero) == 1)
		return ;
	if (nb < 0)
	{
		if (flags.minus == 1)
		{
			write(1, "-", 1);
			flags.minus = 0;
		}
		nb = -nb;
	}
	if (nb >= 10)
	{
		*zero = 1;
		ft_putnbr_printf(nb / 10, flags, &*zero);
		ft_putnbr_printf(nb % 10, flags, &*zero);
	}
	else
	{
		if (nb == 0 && flags.point != -1 && *zero == 0)
			return ;
		nb = nb + '0';
		write(1, &nb, 1);
	}
}

int	ft_argument_di(const char *symbol, va_list argument, t_list flags)
{
	int				score;
	long long int	d;
	int				len;

	flags.zero = 0;
	flags.minus = 0;
	d = 0;
	d = ft_number_size(&*argument, flags, &flags.zero);
	flags = ft_nbrlen(&len, d, flags, &flags.zero);
	flags = ft_point_width_dx(flags, &score, &len, &*symbol);
	flags = ft_filler(&*symbol, flags, len);
	ft_putnbr_printf(d, flags, &flags.zero);
	flags = ft_filler_after(flags);
	return (score);
}
