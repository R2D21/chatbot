#include "../includes/my.h"

void		speak(char *output, char *input)
{
  char		*tmp;

  if ((tmp = malloc(4096 * sizeof(char))) == NULL)
    print_error("[CMD:43] malloc() is fail.\ntmp is NULL\n");
  else
    {
      my_putstr(input);
      my_putchar('\n');
      output = megahal_do_reply(input,1);
      tmp[0] = '\0';
      strcat(tmp, "pico2wave -l fr-FR -w data/output.wav \"");
      strcat(tmp, output);
      strcat(tmp, "\"");
      strcat(tmp, " && aplay data/output.wav");
      system(tmp);
      sleep(1);
    }
}

char		*get_words(char *buff)
{
  int		fd;
  fd = 0;
  fd = open("./data/test.json", O_RDONLY);
  read(fd, buff, 4096);
  return (parse(buff));
}

void  INThandler(int sig)
{
  signal(sig, SIG_IGN);
  megahal_cleanup();
  system("killall ./a.out");
  exit(0);
}

char		*initialise(t_AI *AI)
{
  megahal_setdirectory ("./data/");
  megahal_initialize();
  AI->output = megahal_initial_greeting();
  return (AI->output);
}

char		*command(char *str)
{
  char	*dest;

  if ((dest = malloc(4096 * sizeof(char))) == NULL)
    print_error("\n");
  else
    {
      if ((strcmp(str, "save")) == 0)
	{
	  strcat(dest, "#");
	  strcat(dest, str);
	}
      else if ((strcmp(str, "brain")) == 0)
	{
	  strcat(dest, "#");
	  strcat(dest, str);
	}
      else if ((strcmp(str, "help")) == 0)
	{
	  strcat(dest, "#");
	  strcat(dest, str);
	}
      return (dest);
    }
  return (NULL);
}

t_AI	*realoc(t_AI *AI)
{
  printf("realloc\n");
  free(AI->output);
  free(AI->input);
  free(AI);
  if ((AI  = malloc(1 * sizeof(char))) == NULL)
    print_error("[CMD:41] malloc() is fail.\nAI is NULL\n");
  else
    if ((AI->input = malloc(4096 * sizeof(char))) == NULL)
      print_error("[CMD:39] malloc() is fail.\nAI->input is NULL\n");
    else
      if ((AI->output = malloc(4096 * sizeof(char))) == NULL)
	print_error("[CMD:41] malloc() is fail.\nAI->output is NULL\n");
      else
	if ((AI->buff = malloc(4096 * sizeof(char))) == NULL)
	  print_error("[CMD:41] malloc() is fail.\nAI->buff is NULL\n");
	else
	  {
	    my_putstr("[MOI]");
	return (AI);
	  }
  return (NULL);
}

void		cmd(t_AI *AI)
{
  int		i;

  i = 0;
  my_putstr("[MOI]");
  signal(SIGINT, INThandler);
  while ((AI->input = (char*)get_words(AI->buff)) == NULL || AI->input[0] == '\0')
    {
      if (i++ == 30)
	AI = realoc(AI);
      /* AI->input = get_words(AI); */
      sleep(1);
    }
  speak(AI->output, AI->input);
}
