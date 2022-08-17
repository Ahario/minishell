#include "minishell.h"


void before_init(void)
{
	struct termios	change;

	tcgetattr(0, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &change);
	set_signal(SHE, SHE);
}

int	main(int argc, char *argv[], char **evnp)
{
	t_data			*data;
	struct termios	terminal;

	tcgetattr(0, &terminal);
	before_init(void);
	tcsetattr(0, TCSANOW, &terminal);
	return (0);
}
