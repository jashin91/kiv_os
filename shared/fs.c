/*
fs
*/
#include "../include/structures.h"
#include "../include/constants.h"
#include "../include/common.h"

#define DLLTEST
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //sleep()
#ifdef DLLTEST
/* strchr, declared in string.h, is used in the examples. */
#include <string.h>
#define HEADER
#else
#include "dll.h"
#endif 


void
fs_init (fs_t * fs, char *data)
{
	fs->first = fs->last = 0;
	fs->count = 0;
	fs->data = data;
	for (int i = 0; i < DISK_SIZE; i++) fs->data[i] = 0;
}



/* The following function adds a new file to the end of the fileed
   fs. It allocates memory for it. The contents of the file are
   copied from "data". */

void
fs_mkdir (fs_t * fs, char *name)
{
	file_t * file; /* calloc sets the "next" field to zero. */
	file = calloc (1, sizeof (file_t));
	if (! file) {
		fprintf (stderr, "calloc failed.\n");
		exit (EXIT_FAILURE);
	}
	file->name = name;
	if (fs->last) /* Join the two final files together. */
	{			
		fs->last->next = file;
		file->prev = fs->last;
		fs->last = file;
		file->start = file->prev->start + file->prev->len;
	}
	else {
		fs->first = file;
		fs->last = file;
		file->start = 0;
	}	
	file->type=2;
	file->len = DIR_LEN;
	fs->count++;
	//printf("mkdir: file->start: %i", file->start);
	
	char filename[40]= "Jmeno_souboru_v_tomto_adresari";
	unsigned int len = strlen(filename); //oddělení jména a čísla souboru + číslo souboru (4Bint)
	unsigned int i, j;
	for (i = file->start; i <= len; i++) fs->data[i] = filename[i];
	fs->data[i] = GS;//group sparator
	i++;
	printf("i=%i, len=%i; fs->data[i] = %i; fs->count=%i\n", i, len, fs->data[i], fs->count);
	unsigned char *p_integer;
	p_integer = (unsigned char *) &fs->count;
	unsigned int end_of_num = i + 4; //sizeof(int) = 4B
	printf("i=%i, end_of_item=%i; ", i, end_of_num);
	j=3;
	for (; i < end_of_num; i++)
	{
		fs->data[i] = (unsigned char) p_integer[j];
		j--;
	}
	file->len = i + 1; // info o souboru končí za jednom ETX; 2x ETX je až na konci seznamu souborů
	for (; i<end_of_num+2; i++) fs->data[i] = ETX; //(=3)
	//2x ETX za sebou = konec položky
	/* debug
	*/
	printf("\n");
	for (i = file->start; i < end_of_num+2; i++)
		printf("%i ", fs->data[i]);
	printf("\n");	
	
	unsigned int eof = file->start + file->len;
	printf("mk_dir: file->start/eof: %i / %i", file->start, eof);

	for (i = file->start; fs->data[i] != GS; i++)
		printf("%c", fs->data[i]);
	
	printf("\ni=%i", i);
	printf("\n");
	exit(1);
}


void
fs_file_add (fs_t *fs, char *name, char *data)
{
	file_t * file;

	/* calloc sets the "next" field to zero. */
	file = calloc (1, sizeof (file_t));
	if (! file) {
		fprintf (stderr, "calloc failed.\n");
		exit (EXIT_FAILURE);
	}
	/*
	char dirname[255];
	for (unsigned char i = 1; name[i] != '/'; i++) dirname[i] = name[i];
	printf ("dirname: %s", dirname);
	*/
	file->name = name;
	if (fs->last) {
		/* Join the two final files together. */
		fs->last->next = file;
		file->prev = fs->last;
		fs->last = file;
		//printf("prev_start: %i", file->prev->start);
		file->start = file->prev->start + file->prev->len;
		file->len = strlen(data);
		int eof = file->start + file->len;
		for (int i = file->start + 1; i <= eof; i++)
		{
			int j = 0;
			fs->data[i] = data[j];
		}
		file->type=1;
	}
	else {
		fs->first = file;
		fs->last = file;
		file->start = 0;
		file->len = strlen(data);
		int eof = file->start + file->len;
		for (int i = file->start + 1; i <= eof; i++)
		{
			int j = 0;
			fs->data[i] = data[j];
		}
		file->type=1;
	}	
	fs->count++;
}

void
fs_fw (fs_t * fs, char *name, char *data)
{ //když bude obsah zapisovaného obsahu větší, než je právě zapsaný obsah
	// = aktuální velikost souboru, tak se aktuální soubor smaže a vytvoří se nový
	// s právě zapisovaným obsahem
	fs_file_add ( fs, name, data);
}

void
fs_delete (fs_t * fs, file_t * file)
{
	file_t * prev;
	file_t * next;

	prev = file->prev;
	next = file->next;
	if (prev) {
		if (next) {
			/* Both the previous and next files are valid, so just
			   bypass "file" without altering "fs" at all. */
			prev->next = next;
			next->prev = prev;
		}
		else {
			/* Only the previous file is valid, so "prev" is now the
			   last file in "fs". */
			prev->next = 0;
			fs->last = prev;
		}
	}
	else {
		if (next) {
			/* Only the next file is valid, not the previous one, so
			   "next" is now the first file in "fs". */
			next->prev = 0;
			fs->first = next;
		}
		else {
			/* Neither previous nor next files are valid, so the fs
			   is now empty. */
			fs->first = 0;
			fs->last = 0;
		}
	}
	free (file);
	fs->count--;
}


static void
print_fs (char *name, unsigned int start, unsigned int len)
{
    printf ("\t%s, start: %i, length: %i\n", name, start, len);
}

void
fs_traverse (fs_t * fs)
{
	file_t * file;

	for (file = fs->first; file; file = file->next) {
		print_fs (file->name, file->start, file->len);
	}
}


void
fs_traverse_in_reverse (fs_t * fs)
{
	file_t * file;

	for (file = fs->last; file; file = file->prev)
	{
		print_fs (file->name, file->start, file->len);
		
	}
}


void
fs_traverse_delete (fs_t * fs, char *defined_name)
{
	file_t * file;
	file_t * next;

	for (file = fs->first; file; file = next) {
	next = file->next;
		//printf("rtn: %i", delete_a (file->name));
		if (! strcmp (file->name, defined_name)) {
			fs_delete (fs, file);
		}
	}
}

void
fs_print_file (fs_t * fs, char *path)
{
	file_t * file;
	file_t * next;

	for (file = fs->first; file; file = next)
	{
		next = file->next;
		if (! strcmp (file->name, path)) {
			//printf("Data souboru: %s\n", (char *) file->data);
		}
	}
}

void
fs_ls_dir (fs_t * fs, char *path)
{
	file_t * file;
	file_t * next;
	int eof, i;

	for (file = fs->first; file; file = next)
	{
		next = file->next;
		if (! strcmp (file->name, path))
		{
			eof = file->start + file->len;
			printf("ls_dir: file->start/eof: %i / %i", file->start, eof);
			printf("%s: ", path);
			for (i = file->start; fs->data[i] != GS; i++)
				printf("%c", fs->data[i]);
			//printf("\ni=%i", i);
			printf("\n");
			unsigned int j = i; //konec jména souboru
			for (; j < i+4; j++)
				printf("%i\n", fs->data[j]);
		}
	}
}

/* Free the fs's memory. */

void
fs_free (fs_t * fs)
{
	file_t * file;
	file_t * next;
	for (file = fs->first; file; file = next) {
		/* Store the next value so that we don't access freed
		   memory. */
		next = file->next;
		free (file);
	}
}

#ifdef DLLTEST

/* Example traverse delete function - delete everything. */





#endif /* def DLLTEST */
