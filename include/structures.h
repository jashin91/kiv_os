#ifndef _struktury
#define _struktury
#include "./constants.h"

/*
pouze pro 32 a více bitové systémy
*/


typedef struct file file_t;

struct file
{
	char *name;
	int type;
	unsigned int start;
	unsigned int len;
	file_t * prev;
	file_t * next;
};


typedef struct fs
{
	int count;
	file_t * first;
	file_t * last;
	char *data;	
}
fs_t;
	
	
#endif