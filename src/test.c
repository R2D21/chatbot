#include "my.h"

void usage()
{
    puts("usage: megahal [-[pqrgwbh]]\n" \
	 "\t-h : show usage\n" \
	 "\t-p : inhibit prompts\n" \
	 "\t-q : quiet mode (no replies) enabled at start\n" \
	 "\t-r : inhibit progress display\n" \
	 "\t-g : inhibit initial greeting\n" \
	 "\t-b : inhibit banner display at startup\n");
}

/*===========================================================================*/

/*
 *		Function:	Main
 *
 *		Purpose:		Initialise everything, and then do an infinite loop.  In
 *						the loop, we read the user's input and reply to it, and
 *						do some housekeeping task such as responding to special
 *						commands.
 */
int main(int argc, char **argv)
{
  char *input= malloc(4096 * sizeof (char));
    char *output=NULL;
    int c, fd, option_index = 0;

    while(1) {
	if((c = getopt_long(argc, argv, "hpwb", long_options,
			    &option_index)) == -1)
	    break;
	switch(c) {
	case 'p':
	    megahal_setnoprompt();
	    break;
	case 'w':
	    megahal_setnowrap();
	    break;
	case 'b':
	    megahal_setnobanner();
	    break;
	case 'h':
	    usage();
	    return 0;
	}
    }

    /*
     *		Do some initialisation
     */
    megahal_initialize();


    /*
     *		Create a dictionary which will be used to hold the segmented
     *		version of the user's input.
     */

    /*
     *		Load the default MegaHAL personality.
     */
    output = megahal_initial_greeting();
    megahal_output(output);
    /*
     *		Read input, formulate a reply and display it as output
     */

    while(1) {
      my_putstr("->");
           read(0, input, 4095);
	/*
	 *		If the input was a command, then execute it
	 */
	if (megahal_command(input) != 0)
	    continue;
	/* strcpy(input, "Bonjour\n\0"); */
	output = megahal_do_reply(input, 1);
	/* printf("%s\n", output); */
	megahal_output(output);
    }

    megahal_cleanup();
    exit(0);
}
