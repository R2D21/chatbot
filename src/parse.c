#include "../includes/my.h"

char	*parse(char *tmp)
{
  char		*str;
  char		**tab;

  tab = NULL;
  if ((str = malloc(4096 * sizeof(char))) == NULL)
    print_error("[PARSE:10] Error: malloc is fail.str is NULL\n");
  else
    if ((str = parse_file(tmp)) == NULL)
      {
	free(str);
	print_error("[PARSE:15] ERROR parse_file() is fail.str is NULL\n");
      }
    else
      {
	if ((tab = malloc_tab(tab)) == NULL)
	  print_error("");
	else
	  {
	    tab = my_str_to_wordtab(parse_str(str, '[',']'), '\"');
	    free(str);
	    if (tab[0] != '\0')
	      return (tab[4]);
	  }
      }
  return (NULL);
}

char		*parse_file(char *tmp)
{
  int		j;
  int		i;
  char		*str;

  j = 0;
  i = 0;
  if ((  str = malloc(4096 * sizeof(char))) == NULL)
    print_error("Erreor\n");
  else
    {
      while (tmp[i] != '\0' && tmp[i] != '}' && tmp[i+1] != ']')
	i++;
      i += 3;
      while (tmp[i] != '\0')
	str[j++] = tmp[i++];
      str[j] = '\0';
      return (str);
    }
  return (NULL);
}

char		*parse_str(char *tmp, char c, char t)
{
  char		*str;
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((str = alloca(4096 * sizeof(char))) == NULL)
    print_error("[test]\n");
  else
    {
      while (tmp[i] != '\0' && tmp[i] != c)
	i++;
      i+=3;
      while (tmp[i] != '\0'
	     && tmp[i] != t)
	str[j++] = tmp[i++];
      str[j] = '\0';
      return (str);
    }
  return (NULL);
}
