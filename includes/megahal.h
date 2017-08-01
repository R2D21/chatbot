#ifndef __MEGAHAL_H__
# define __MEGAHAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <getopt.h>
#if !defined(AMIGA) && !defined(__mac_os)
#include <malloc.h>
#endif
#include <string.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#if defined(__mac_os)
#include <types.h>
#include <Speech.h>
#else
#include <sys/types.h>
#endif
#include "megahal.h"
#if defined(DEBUG)
#include "debug.h"
#endif
/* static struct option long_options[] = { */
/*     {"no-prompt", 0, NULL, 'p'}, */
/*     {"no-wrap", 0, NULL, 'w'}, */
/*     {"no-banner", 0, NULL, 'b'}, */
/*     {"help", 0, NULL, 'h'}, */
/*     {0, 0, 0, 0} */
/* }; */

#define P_THINK 40
#define D_KEY 100000
#define V_KEY 50000
#define D_THINK 500000
#define V_THINK 250000

#define MIN(a,b) ((a)<(b))?(a):(b)

#define COOKIE "MegaHALv8"
#define TIMEOUT 1

#define DEFAULT "."

#define COMMAND_SIZE (sizeof(command)/sizeof(command[0]))

#define BYTE1 unsigned char
#define BYTE2 unsigned short
#define BYTE4 unsigned long

#ifdef __mac_os
#define bool Boolean
#endif

#ifdef DOS
#define SEP "\\"
#else
#define SEP "/"
#endif

#ifdef AMIGA
#undef toupper
#define toupper(x) ToUpper(x)
#undef tolower
#define tolower(x) ToLower(x)
#undef isalpha
#define isalpha(x) IsAlpha(_AmigaLocale,x)
#undef isalnum
#define isalnum(x) IsAlNum(_AmigaLocale,x)
#undef isdigit
#define isdigit(x) IsDigit(_AmigaLocale,x)
#undef isspace
#define isspace(x) IsSpace(_AmigaLocale,x)
#endif

#ifndef __mac_os
#undef FALSE
#undef TRUE
typedef enum { FALSE, TRUE } bool;
#endif

typedef struct {
    BYTE1 length;
    char *word;
} STRING;

typedef struct {
    BYTE4 size;
    STRING *entry;
    BYTE2 *index;
} DICTIONARY;

typedef struct {
    BYTE2 size;
    STRING *from;
    STRING *to;
} SWAP;

typedef struct NODE {
    BYTE2 symbol;
    BYTE4 usage;
    BYTE2 count;
    BYTE2 branch;
    struct NODE **tree;
} TREE;

typedef struct {
    BYTE1 order;
    TREE *forward;
    TREE *backward;
    TREE **context;
    DICTIONARY *dictionary;
} MODEL;

typedef enum { UNKNOWN, QUIT, EXIT, SAVE, DELAY, HELP, SPEECH, VOICELIST, VOICE, BRAIN, QUIET} COMMAND_WORDS;

typedef struct {
    STRING word;
    char *helpstring;
    COMMAND_WORDS command;
} COMMAND;

/*===========================================================================*/

static int width=75;
static int order=5;

static bool typing_delay=FALSE;
static bool noprompt=FALSE;
static bool speech=FALSE;
static bool quiet=FALSE;
static bool nowrap=FALSE;
static bool nobanner=FALSE;

static char *errorfilename = "megahal.log";
static char *statusfilename = "megahal.txt";
static DICTIONARY *words=NULL;
static DICTIONARY *greets=NULL;
static MODEL *model=NULL;

static FILE *errorfp;
static FILE *statusfp;

static DICTIONARY *ban=NULL;
static DICTIONARY *aux=NULL;
/*static DICTIONARY *fin=NULL; not used */
static DICTIONARY *grt=NULL;
static SWAP *swp=NULL;
static bool used_key;
static char *directory=NULL;
static char *last=NULL;

static COMMAND command[] = {
    { { 4, "QUIT" }, "quits the program and saves MegaHAL's brain", QUIT },
    { { 4, "EXIT" }, "exits the program *without* saving MegaHAL's brain", EXIT },
    { { 4, "SAVE" }, "saves the current MegaHAL brain", SAVE },
    { { 5, "DELAY" }, "toggles MegaHAL's typing delay (off by default)", DELAY },
    { { 6, "SPEECH" }, "toggles MegaHAL's speech (off by default)", SPEECH },
    { { 6, "VOICES" }, "list available voices for speech", VOICELIST },
    { { 5, "VOICE" }, "switches to voice specified", VOICE },
    { { 5, "BRAIN" }, "change to another MegaHAL personality", BRAIN },
    { { 4, "HELP" }, "displays this message", HELP },
    { { 5, "QUIET" }, "toggles MegaHAL's responses (on by default)",QUIET},
    /*
      { { 5, "STATS" }, "Display stats", STATS},
      { { 5, "STATS-SESSION" }, "Display stats for this session only",STATS_SESSION},
      { { 5, "STATS-ALL" },"Display stats for the whole lifetime",STATS-ALL},
    */
};

#ifdef AMIGA
struct Locale *_AmigaLocale;
#endif

#ifdef __mac_os
Boolean gSpeechExists = false;
SpeechChannel gSpeechChannel = nil;
#endif

/* FIXME - these need to be static  */

char	*strdup(const char *s);
static void add_aux(MODEL *, DICTIONARY *, STRING);
static void add_key(MODEL *, DICTIONARY *, STRING);
static void add_node(TREE *, TREE *, int);
static void add_swap(SWAP *, char *, char *);
static TREE *add_symbol(TREE *, BYTE2);
static BYTE2 add_word(DICTIONARY *, STRING);
static int babble(MODEL *, DICTIONARY *, DICTIONARY *);
static bool boundary(char *, int);
static void capitalize(char *);
/* static void changevoice(DICTIONARY *\/\* , int *\/); */
static void change_personality(DICTIONARY *, unsigned int, MODEL **);
static void delay(char *);
/* static void die(int); */
static bool dissimilar(DICTIONARY *, DICTIONARY *);
static void error(char *, char *, ...);
static float evaluate_reply(MODEL *, DICTIONARY *, DICTIONARY *);
static COMMAND_WORDS execute_command(DICTIONARY *, int *);
static void exithal(void);
static TREE *find_symbol(TREE *, int);
static TREE *find_symbol_add(TREE *, int);
static BYTE2 find_word(DICTIONARY *, STRING);
static char *generate_reply(MODEL *, DICTIONARY *);
static void help(void);
static void ignore(int);
static bool initialize_error(char *);
#ifdef __mac_os
static bool initialize_speech(void);
#endif
static bool initialize_status(char *);
static void learn(MODEL *, DICTIONARY *);
static void listvoices(void);
static void make_greeting(DICTIONARY *);
static void make_words(char *, DICTIONARY *);
static DICTIONARY *new_dictionary(void);

static char *read_input(char *);
static void save_model(/* char *, */ MODEL *);
#ifdef __mac_os
static char *strdup(const char *);
#endif
static void upper(char *);
static void write_input(char *);
static void write_output(char *);
#if defined(DOS) || defined(__mac_os)
static void usleep(int);
#endif

static char *format_output(char *);
static void free_dictionary(DICTIONARY *);
static void free_model(MODEL *);
static void free_tree(TREE *);
static void free_word(STRING);
static void free_words(DICTIONARY *);
static void initialize_context(MODEL *);
static void initialize_dictionary(DICTIONARY *);
static DICTIONARY *initialize_list(char *);
static SWAP *initialize_swap(char *);
static void load_dictionary(FILE *, DICTIONARY *);
static bool load_model(char *, MODEL *);
static void load_personality(MODEL **);
static void load_tree(FILE *, TREE *);
static void load_word(FILE *, DICTIONARY *);
static DICTIONARY *make_keywords(MODEL *, DICTIONARY *);
static char *make_output(DICTIONARY *);
static MODEL *new_model(int);
static TREE *new_node(void);
static SWAP *new_swap(void);
static bool print_header(FILE *);
static bool progress(char *, int, int);
static DICTIONARY *reply(MODEL *, DICTIONARY *);
static void save_dictionary(FILE *, DICTIONARY *);
static void save_tree(FILE *, TREE *);
static void save_word(FILE *, STRING);
static int search_dictionary(DICTIONARY *, STRING, bool *);
static int search_node(TREE *, int, bool *);
static int seed(MODEL *, DICTIONARY *);
static void show_dictionary(DICTIONARY *);
/* static void speak(char *); */
static bool status(char *, ...);
static void train(MODEL *, char *);
static void typein(char);
static void update_context(MODEL *, int);
static void update_model(MODEL *, int);
static bool warn(char *, char *, ...);
static int wordcmp(STRING, STRING);
static bool word_exists(DICTIONARY *, STRING);
static int rnd(int);
void	my_putstr(char * str);


#endif /* !__MY_H__ */
