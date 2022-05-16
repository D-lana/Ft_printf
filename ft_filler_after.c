#include "ft_printf.h"

t_list	ft_filler_after(t_list flags)
{
	while (flags.width > 0 && flags.fill_in == 1)
	{
		flags.width--;
		write(1, " ", 1);
	}
	return (flags);
}
