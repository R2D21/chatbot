/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/sylvia_r//Desktop/projet/lib/my
** 
** Made by romain sylvian
** Login   <sylvia_r@epitech.net>
** 
** Started on  Tue Nov 16 08:44:42 2010 romain sylvian
** Last update Wed Mar  2 19:44:22 2011 romain sylvian
*/

#include <stdio.h>
#include <stdlib.h>

int	cpt_word(char *str, char c)
{
  int	i;
  int	cpt;
  char	car_prec;

  i = 0;
  cpt = 0;
  car_prec = c;
  while (str[i] != '\0')
    {
      if ((car_prec == c) && (str[i] != c))
	{
	  cpt++;
	}
      car_prec = str[i];
      i++;
    }
  return (cpt);
}

char	*copy(char *str, char *dest, int debut, char c)
{
  int	i;

  i = 0;
  while ((str[debut] != c) && (str[debut] != '\0'))
    {
      dest[i] = str[debut];
      debut++;
      i++;
    }
  dest[i] = '\0';
  return (dest);
}

int	cpt_letter(char *str, int debut, char c)
{
  int	i;

  i = 0;
  while ((str[debut] != c) && (str[debut] != '\0'))
    {
      debut++;
      i++;
    }
  return (i);
}

char	**my_str_to_wordtab(char *str, char c)
{
  int	i;
  int	j;
  char	car_prec;
  char	**tab;

  i = 0;
  j = 0;
  tab = malloc((cpt_word(str, c) + 1) * sizeof(*tab));
  car_prec = c;
  while (str[i] != '\0')
    {
      if ((car_prec == c) && (str[i] != c))
	{
	  tab[j] = malloc((cpt_letter(str, i, c) + 1) * sizeof(**tab));
	  copy(str, tab[j], i, c);
	  j++;
	}
      car_prec = str[i];
      i++;
    }
  tab[j] = NULL;
  return (tab);
}
