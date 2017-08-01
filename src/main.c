#include "../includes/my.h"

int		main()
{
  t_AI		*AI;

  if ((AI = malloc(1 *sizeof(t_AI))) == NULL)
    print_error("[CMD:39] malloc() is fail.\nAI is NULL\n");
  else
    {
      if ((AI->output = malloc(4096 * sizeof(char))) == NULL)
	print_error("[CMD:39] malloc() is fail.\noutput is NULL\n");
      if ((AI->input = malloc(4096 * sizeof(char))) == NULL)
	print_error("[CMD:39] malloc() is fail.\ninput is NULL\n");
      if ((AI->buff = malloc(4096 * sizeof(char))) == NULL)
	print_error("OOK\n");
      else
	{
	  strcpy(AI->output, initialise(AI));
	  while (1)
	    {
	      if (megahal_command(command(AI->input)) != 0)
		continue;
	      cmd(AI);
	    }
	}
      return (0);
    }
  return (1);
}
