#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	my_putchar(char c)
{
  write(0, &c, 1);
}

void	my_putstr(char * str)
{
  write(0, str, strlen(str));
}

void	my_puttab(char **tab)
{
  int i;
  
  i = 0;
  while (tab[i] != NULL)
    {
      write(0, tab[i], strlen(tab[i]));
      write(0, "\n", 2);
      i++;
    }
}

void	print_error(char *str)
{
    write(2, str, strlen(str));
    exit(1);
}
