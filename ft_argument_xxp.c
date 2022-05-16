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

static size_t	ft_len_xxp(unsigned long long int nb, t_list flags, int *zero)
{
	size_t					i;
	unsigned long long int	nb2;

	i = 0;
	nb2 = (unsigned long long int) nb;
	if (nb == 0 && ((flags.width != 0 && flags.point == 0) || flags.point == 0))
		return (*zero = 0);
	while (nb2 >= 16)
	{
		nb2 = nb2 / 16;
		i++;
	}
	if (nb2 < 0)
	{
		nb2 = -nb2;
		while (nb2 >= 16)
		{
			nb2 = nb2 / 16;
			i++;
		}
	}
	i++;
	return (i);
}

static void	ft_putnbr_xxp(const char *symbol, t_list flags, size_t nb, int *z)
{
	if (nb < 0)
		nb = -nb;
	if (nb >= 16)
	{
		*z = 1;
		ft_putnbr_xxp(symbol, flags, nb / 16, &*z);
		ft_putnbr_xxp(symbol, flags, nb % 16, &*z);
	}
	else if (nb < 16 && nb > 9)
	{
		nb = nb % 10;
		if (*symbol == 'x' || *symbol == 'p')
			nb = nb + 97;
		else if (*symbol == 'X')
			nb = nb + 65;
		write(1, &nb, 1);
	}
	else if (nb <= 9)
	{
		if (nb == 0 && *z == 0)
			return ;
		nb = nb + '0';
		write(1, &nb, 1);
	}
}

int	ft_argument_xxp(const char *symbol, va_list argument, t_list flags)
{
	int				score;
	int				len;
	size_t			xxp;
	size_t			p;

	flags.zero = -1;
	flags.minus = 0;
	if (*symbol == 'p')
	{
		p = va_arg(&*argument, size_t);
		len = ft_len_xxp((long int) p, flags, &flags.zero) + 2;
		xxp = (size_t) p;
	}
	if (*symbol == 'x' || *symbol == 'X')
	{
		xxp = ft_number_size_u(&*argument, flags);
		len = ft_len_xxp(xxp, flags, &flags.zero);
	}
	if (xxp == 0)
		flags.b = 0;
	flags = ft_point_width_dx(flags, &score, &len, &*symbol);
	flags = ft_filler(&*symbol, flags, len);
	ft_putnbr_xxp(&*symbol, flags, xxp, &flags.zero);
	flags = ft_filler_after(flags);
	return (score);
}
