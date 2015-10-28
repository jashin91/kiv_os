#ifndef _struktury
#define _struktury
#include "./konstanty.h"


typedef struct config_parms
{
	char workdir[200]; //max. délka cesty do prac. adresáře
	char run_as_user[20];
	char users_home[220]; //adresář pro uživatelský bordel
	char db_executable[50]; //cesta k databázové binárce
	char db_user[20];
	char db_heslo[20];
	char log_path[200];
	unsigned short loglevel;
	unsigned int whisky;

	
} CONFIG_PARMS;
	
	
#endif