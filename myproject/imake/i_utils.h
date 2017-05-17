#ifndef I_UTILS_H_ 
#define I_UTILS_H_ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <dirent.h>
#include <sys/stat.h>

//#if defined CONFIG_USER_STORAGE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#endif

#define CMDLEN		256

#define MBSSID_MAX_NUM 8


#define LOGFILE	"/dev/console"

void do_system(char *fmt, ...);


#endif 
