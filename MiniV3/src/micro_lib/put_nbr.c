#include "../../minishell.h"

void	ft_putnbr(int n)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar_fd(nb % 10 + '0', 1);
	}
	else
		ft_putchar_fd(nb + '0', 1);
}
