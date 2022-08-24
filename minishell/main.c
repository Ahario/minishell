#include "minishell.h"

t_arg *set_cmd(char *ch)
{
	t_arg	*cmd;
	int			i;

	i = 0;
	char	**ac;
	int		type;
	int		fd_in;
	int		fd_out;
	int		if_next;
	return (cmd);
}

void parse(char *ch, t_data *data)
{
	int			i;
	char **str;

	str = ft_split(ch, " ");
	i = 0;

	data->argv = str;
	data->argc = ft_strlen(ch);

	while(str[i] != NULL)
		printf("%s\n", str[i++]);
}

void before_init(void)
{
	struct termios	change;

	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
}

int	main(int argc, char *argv[], char **envp)  
{
	t_data			data;
	struct termios	terminal;
	char			*ch;

	tcgetattr(STDIN_FILENO, &terminal);
	before_init();
	data.envp = envp;
	while(1)
	{
		ch = readline("MINISHELL./ ");
//		sunglee_signal_here;
		if (ch)
			parse(ch, &data);
		add_history(ch);
		free(ch);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}

