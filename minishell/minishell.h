#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_data{
	int		nac;
	char	**ngv;
	char	**nev;
}	t_data;

void before_init(void);

#endif