#ifndef MY_H_
# define MY_H_

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct	s_AI
{
  char		*input;
  char		*output;
  char		*buff;
}		t_AI;

int		megahal_command(char *input);

char		*command(char *str);
char		*get_words(char *str);
char		*initialise(t_AI *AI);
char		*megahal_do_reply(char *input, int log);
char		*megahal_initial_greeting(void);
char		*parse(char *tmp);
char		*parse_file(char *tmp);
char		*parse_str(char *tmp, char c, char t);

char		**malloc_tab(char **tab);
char		**my_str_to_wordtab(char *str, char c);

void		cmd(t_AI *AI);
void		INThandler(int);
void		megahal_cleanup(void);
void		megahal_initialize(void);
void		megahal_output(char *output);
void		megahal_setdirectory (char *dir);
void		my_putchar(char c);
void		my_putstr(char * str);
void		my_puttab(char **tab);
void		print_error(char *str);
void		speak(char *output, char *input);

#endif
