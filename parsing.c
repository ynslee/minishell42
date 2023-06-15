
#include "minishell.h"

/* parsing order
1. Readline using readline function
2. lexical analysis
	2-1)skip whitespace
	2-2)deal with quotation marks(?)
	2-3)identify token
3. syntax analysis
	3-1)Check grammar rules: https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02
*/



/*--------------lexical analysis------------------*/
/*T as token*/

#define T_NULL 0
#define T_WORD 1
#define T_REDIRECT 2
#define T_PIPE 3
#define T_DOUBLE_QUOTES 4
#define T_SINGLE_QUOTES 5

typedef struct s_token{
	int		type;
	char	*str;
}	t_token;

/*if input: <file cat | grep " "

str: "<", "file", "cat", "|", "grep", "" "", NULL
type: REDIRECT, WORD, WORD, PIPE, WORD, WORD, NULL*/


/*--------------syntax analysis------------------*/
//if you don't understand the things below, look at example codes or parsing idea picture
//and come back to see what I'm thinking!

// <pipeline>    :	 <cmd>
//               |   <pipeline> '|' <cmd>

// <cmd>          : <simple_cmd> 
//                |   <simple_cmd> <redirects>

// <simple_cmd>   : <file_path>
//                |   <argv>

// <argv>         : <file_path> <args>

// <redirects>    : <io_redirect>
//                 |  <redirects> <io_redirect>

// <io_redirect>  : '<'   <filename>
//                |  '<<'  <filename>
//                |  '>'   <filename>
//                |  '>>'  <filename>

// <args>        : WORD 
//               | <args> WORD

// <filename>    : WORD

// <file_path>   : WORD

//for example, this would be the way of taking syntax:

t_token token;

void	syntax_simple_cmd()
{
	if (token.type == T_WORD)
	{
		if (token.type == T_WORD)
			;
	}
	else
		return (fail_to_find_cmd);
}

void	syntax_cmd()
{
	syntax_simple_cmd();
	if (token.type == T_REDIRECT)
		syntax_redirects();
}

void	syntax_pipeline()
{
	syntax_cmd();
	if (token.type == T_PIPE)
		syntax_pipeline();
}








//-----------------not related------------------
// void	handler(int signum)
// {
// 	if (signum != SIGINT)
// 		return ;
// 	printf("ctrl + c\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// }

// int	main(void)
// {
// 	int		ret;
// 	char	*line;

// 	ret = 0;
// 	signal(SIGINT, handler);
// 	while (1)
// 	{
// 		line = readline("input> ");
// 		if (line)
// 		{
// 			if (ret)
// 				printf("output> %s\n", line);
// 			add_history(line);
// 			free(line);
// 			line = NULL;
// 		}
// 		else
// 		{
// 			printf("ctrl + d\n");
// 		}
// 	}
// 	return (0);
// }
