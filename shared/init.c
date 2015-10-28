/****************************************
**** 			bla bla 			***
****************************************/

#include <stdio.h>
#include "../include/shell.h"
#include "../include/konstanty.h"
#include "../include/struktury.h"

void print_usage(void)
{
	printf("\n\nUssage:\t\t-c <config_file>\t\t: Path to the config file.\n\t\t-f \'I_want_to_prone_the_db\'\t: Move data from config to db\n\t\t\t\t\t\t   and replace it.\n\t\t-h|?\t\t\t\t: print this ussage\n\n");
	exit (0);
}

void print_err_usage(char *vstup)
{
	printf("\nUnexpected parameter \"%s\" \n\n", vstup);
	printf("Ussage:\t\t-c <config_file>\t\t: Path to the config file.\n\t\t-f \'I_want_to_prone_the_db\'\t: Move data from config to db\n\t\t\t\t\t\t   and replace it.\n\t\t-h|?\t\t\t\t: print this ussage\n\n");
	exit (1);
}


int main(int argc char **argv)
{
	printf("Inicializace...\n");
	int rtn;
	int opt;

	if (argc <= 1) print_usage();
	
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
	};
	
	//zkusit  touch s aktuálním oprávněním
	
	CONFIG_PARMS konfigurace;
	/* fs */
	
	rtn = shell();
	
	return rtn;
}