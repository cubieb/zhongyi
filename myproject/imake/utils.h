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


/*
 * For cgi
 */
int get_nth_value(int index, char *value, char delimit, char *result, int len);


void convert_string_display(char *str);



#define DBG_MSG(fmt, arg...)	do {	FILE *log_fp = fopen(LOGFILE, "w+"); \
	if(log_fp == NULL) break;\
	fprintf(log_fp, "%s:%s:%d:" fmt "\n", __FILE__, __func__, __LINE__, ##arg); \
	fclose(log_fp); \
} while(0)


/*
 * For web
 *
 */
void web_debug_header(void);
#endif 
