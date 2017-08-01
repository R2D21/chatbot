#include "../../includes/my.h"

char	**malloc_tab(char **tab)
{
  int	i;

  i = 0;
  if ((tab = malloc(4096 * sizeof(char*))) == NULL)
    printf("Error\n");
  else
    {
      while (i < 4096)
	{
	  if ((tab[i] = malloc(4096 *sizeof (char))) == NULL)
	    printf("Error\n");
	  else
	    i++;
	}
      return (tab);
    }
  return (NULL);
}
