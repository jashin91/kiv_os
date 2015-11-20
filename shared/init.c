/****************************************
**** 			bla bla 			***
****************************************/

#include <stdio.h>
#include <stdlib.h> //malloc(), free()
//#include <string.h>
#include <unistd.h> //sleep()
#include "../include/shell.h"
#include "../include/common.h"
#include "../include/constants.h"
#include "../include/structures.h"


void print_usage(void)
{
	//printf("\n\nUssage:\t\t-c <config_file>\t\t: Path to the config file.\n\t\t-f \'I_want_to_prone_the_db\'\t: Move data from config to db\n\t\t\t\t\t\t   and replace it.\n\t\t-h|?\t\t\t\t: print this ussage\n\n");
	printf("\n\nSpusť mi s parametrem '/bin'\n\n");
	exit (0);
}

void print_err_usage(char *vstup)
{
	printf("\nUnexpected parameter \"%s\" \n\n", vstup);
	printf("Ussage:\t\t-c <config_file>\t\t: Path to the config file.\n\t\t-f \'I_want_to_prone_the_db\'\t: Move data from config to db\n\t\t\t\t\t\t   and replace it.\n\t\t-h|?\t\t\t\t: print this ussage\n\n");
	exit (1);
}


int main(int argc, char **argv)
{
	printf("Inicializace...\n");
	int rtn = 0;


	if (argc <= 1) print_usage();
	/*
	int opt;
	while ((opt = getopt(argc, argv, "f:c:u:p:g:m:h")) != -1)
	switch (opt) 

		case 'c': config_path = optarg;  // filename
			break;
		case 'h': print_usage(); 
			break;
		case 'f': firstrun = optarg; //pro vynulování databáze musí obsahovat 'I_want_to_prone_the_db'
			break;
		
		default: print_err_usage(optarg);
			break;
	
	//zkusit  touch s aktuálním oprávněním
	*/
	/* Make a fs of words and then print them out. */


	fs_t fs;
	char *data;
	data = malloc(DISK_SIZE); //bez metadat
	fs_init (&fs, data);
	fs_mkdir (&fs, "/bin");
	fs_mkdir (&fs, "/dev");
	fs_mkdir (&fs, "/proc");
	fs_mkdir (&fs, "/tmp");
	fs_mkdir (&fs, "/var");
	fs_file_add (&fs, "/tmp/dingo", "data souboru");
	fs_file_add (&fs, "/tmp/kangaroo", "vnitřek souboru");
	fs_file_add (&fs, "/tmp/koala", "vnitřek dalšího souboru");
	fs_file_add (&fs, "/tmp/wallaroo", "vnitřek souboru..");
	printf ("Australian animals, in reverse alphabetical order:\n");
	fs_traverse_in_reverse (&fs);
	printf ("\n");
	//printf ("Delete wallaroo:\n");
	//fs_traverse_delete (&fs, "/tmp/wallaroo");
	printf ("\n");
	fs_traverse (&fs);
	printf ("\n");
	//fs_print_file(&fs, argv[1]); //*fs, path + filename
	fs_ls_dir(&fs, argv[1]); //*fs, path + name of dirrectory
	printf ("\n");
	sleep(1);
	fs_free (&fs);
	free(data);


	/* fs */
	
	//rtn = shell();
	
	return rtn;
}

