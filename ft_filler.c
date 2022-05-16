#include "ft_printf.h"

static t_list	ft_znak(t_list flags)
{
	if (flags.minus != 1 && flags.b == 2)
		write(1, "+", 1);
	if (flags.minus == 1)
	{
		write(1, "-", 1);
		flags.minus = 0;
	}
	return (flags);
}

t_list	ft_filler(const char *s, t_list flags, int len)
{
	while (flags.width > 0 && flags.fill_in != 1
		&& (flags.point != -1 || flags.fill_in != 0))
	{
		flags.width--;
		write(1, " ", 1);
	}
	if (*s == 'p' || (*s == 'x' && flags.b == 1))
		write(1, "0x", 2);
	if (*s == 'X' && flags.b == 1)
		write(1, "0X", 2);
	if ((*s == 'd' || *s == 'i') && flags.b == 3 && flags.minus == 0)
		write(1, " ", 1);
	if (flags.minus == 1 || (flags.b == 2 && (*s == 'd' || *s == 'i')))
		flags = ft_znak(flags);
	while (flags.width > 0 && flags.point == -1 && flags.fill_in == 0)
	{
		flags.width--;
		write(1, "0", 1);
	}
	while (flags.point > len)
	{
		flags.point--;
		write(1, "0", 1);
	}
	return (flags);
}
