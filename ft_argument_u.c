#include "ft_printf.h"

static unsigned long long int	ft_number_size_u(va_list argument, t_list flags)
{
	unsigned long long int	u;

	if (flags.lh == 5)
		u = va_arg(argument, unsigned long int);
	if (flags.lh == 6)
		u = va_arg(argument, unsigned long long int);
	if (flags.lh != 5 && flags.lh != 6)
	{
		u = va_arg(argument, unsigned int);
		if (flags.lh == 7)
			u = (unsigned short int) u;
		if (flags.lh == 8)
			u = (unsigned char) u;
	}
	return (u);
}

static t_list	ft_nbrlen(int *len, unsigned long long int nb, t_list flags)
{
	int	i;

	i = 0;
	*len = 0;
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

static void	ft_putnbr_printf(unsigned long long int nb, t_list flags, int *zero)
{
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

int	ft_argument_u(const char *symbol, va_list argument, t_list flags)
{
	int							score;
	unsigned long long int		u;
	int							len;

	flags.zero = 0;
	flags.minus = 0;
	u = ft_number_size_u(&*argument, flags);
	flags = ft_nbrlen(&len, u, flags);
	flags = ft_point_width_dx(flags, &score, &len, &*symbol);
	flags = ft_filler(&*symbol, flags, len);
	ft_putnbr_printf(u, flags, &flags.zero);
	flags = ft_filler_after(flags);
	return (score);
}
