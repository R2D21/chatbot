#include "../includes/megahal.h"

/*---------------------------------------------------------------------------*/

/*
 *		Function:	Save_Dictionary
 *
 *		Purpose:		Save a dictionary to the specified file.
 */
void save_dictionary(FILE *file, DICTIONARY *dictionary)
{
    register unsigned int i;

    fwrite(&(dictionary->size), sizeof(BYTE4), 1, file);
    progress("Saving dictionary", 0, 1);
    for(i=0; i<dictionary->size; ++i) {
	save_word(file, dictionary->entry[i]);
	progress(NULL, i, dictionary->size);
    }
    progress(NULL, 1, 1);
}

/*---------------------------------------------------------------------------*/

/*
 *		Function:	Save_Word
 *
 *		Purpose:		Save a dictionary word to a file.
 */
void save_word(FILE *file, STRING word)
{
    register unsigned int i;

    fwrite(&(word.length), sizeof(BYTE1), 1, file);
    for(i=0; i<word.length; ++i)
	fwrite(&(word.word[i]), sizeof(char), 1, file);
}

void		save_model(MODEL *model)
{
  FILE		*file;
  static char	*filename=NULL;

  if(filename==NULL) filename=(char *)malloc(sizeof(char)*1);

  /*
   *    Allocate memory for the filename
   */
  filename=(char *)realloc(filename,
			   sizeof(char)*(strlen(directory)+strlen(SEP)+12));
  if(filename==NULL) error("save_model","Unable to allocate filename");

  show_dictionary(model->dictionary);
  if(filename==NULL) return;

  /* sprintf(filename, "%s%smegahal.brn", directory, SEP); */
  file=fopen(filename, "wb");
  if(file==NULL) {
    warn("save_model", "Unable to open file `%s'", filename);
    return;
  }

  fwrite(COOKIE, sizeof(char), strlen(COOKIE), file);
  fwrite(&(model->order), sizeof(BYTE1), 1, file);
  save_tree(file, model->forward);
  save_tree(file, model->backward);
  save_dictionary(file, model->dictionary);
  fclose(file);
}

void save_tree(FILE *file, TREE *node)
{
    static int level=0;
    register unsigned int i;

    fwrite(&(node->symbol), sizeof(BYTE2), 1, file);
    fwrite(&(node->usage), sizeof(BYTE4), 1, file);
    fwrite(&(node->count), sizeof(BYTE2), 1, file);
    fwrite(&(node->branch), sizeof(BYTE2), 1, file);

    if(level==0) progress("Saving tree", 0, 1);
    for(i=0; i<node->branch; ++i) {
	++level;
	save_tree(file, node->tree[i]);
	--level;
	if(level==0) progress(NULL, i, node->branch);
    }
    if(level==0) progress(NULL, 1, 1);
}
