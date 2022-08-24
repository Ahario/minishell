#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_data{
	t_arg	*cmd;
	int		argc;
	char	**argv;
	char	**envp;
}	t_data;

typedef struct s_arg{
	char	*ac;
	int		type;
	int		fd_in;
	int		fd_out;
	int		if_next;
}	t_arg;

enum	e_pars{
    NORM, SPCE, SINQ, DOUQ, BSLA, DOLR,
    PIPE, DPIP, SEMC, DSEM,
    RIGT, DRGT, LEFT
};
   
void	before_init(void);
void	parse(char *ch, t_data *data);
t_arg	*set_cmd(char *ch);

#endif