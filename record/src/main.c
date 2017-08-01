#include "../../includes/my.h"

int	main()
{
  while (1)
    {
      system("./scripts/script.sh");
      printf("Vous pouvez parler à nouveau dans 5 secondes\n");
      sleep(5);
    }
  return (0);
}
