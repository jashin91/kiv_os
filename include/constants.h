
#include <stdint.h>
#define TRUE 1
#define FALSE 0
#define BOOL uint_fast8_t


#define DISK_SIZE 8000000 // 8 MB ram disk
#define DIR_LEN 65536 //256 files in dir, 4B=32b=count, 251B=name; 1B=null
#define ETX 3	//end of text
#define FS 28 //file separator
#define GS 29 //group separator
