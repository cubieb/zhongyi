/*
 * 
 *
 *
 */

#include "utils.h"

#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/wireless.h>

#include <stdarg.h>

#include <errno.h>

static char cmd[CMDLEN];

void do_system(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsprintf(cmd, fmt, ap);
	va_end(ap);
	//LOGFILE在.h文件中
	snprintf(cmd, sizeof(cmd),"%s 1>%s 2>&1", cmd, LOGFILE);
	system(cmd);

	return;
}

/*
 * For cgi
 */
int get_nth_value(int index, char *value, char delimit, char *result, int len)
{
	int i=0, result_len=0;
	char *begin, *end;

	if(!value || !result || !len)
		return -1;

	begin = value;
	//返回指向字符串begin 中第一个字符delimit的指针
	end = strchr(begin, delimit);

	while(i<index && end){
		begin = end+1;
		end = strchr(begin, delimit);
		i++;
	}

	//no delimit
	if(!end){
		if(i == index){
			end = begin + strlen(begin);
			result_len = (len-1) < (end-begin) ? (len-1) : (end-begin);
		}else
			return -1;
	} else {
		result_len = (len-1) < (end-begin)? (len-1) : (end-begin);
	}

	memcpy(result, begin, result_len );
	*(result+ result_len ) = '\0';

	return 0;
}




void convert_string_display(char *str)
{
	int  len, i;
	char buffer[193];
	char *pOut;

	memset(buffer,0,193);
	len = strlen(str);
	pOut = &buffer[0];

	for (i = 0; i < len; i++) {
		switch (str[i]) {
			case 38:
				strcpy (pOut, "&amp;");		// '&'
				pOut += 5;
				break;

			case 60:
				strcpy (pOut, "&lt;");		// '<'
				pOut += 4;
				break;

			case 62:
				strcpy (pOut, "&gt;");		// '>'
				pOut += 4;
				break;

			case 34:
				strcpy (pOut, "&#34;");		// '"'
				pOut += 5;
				break;

			case 39:
				strcpy (pOut, "&#39;");		// '''
				pOut += 5;
				break;
			case 32:
				strcpy (pOut, "&nbsp;");	// ' '
				pOut += 6;
				break;

			default:
				if ((str[i]>=0) && (str[i]<=31)) {
					//Device Control Characters
					sprintf(pOut, "&#%02d;", str[i]);
					pOut += 5;
				} else if ((str[i]==39) || (str[i]==47) || (str[i]==59) || (str[i]==92)) {
					// ' / ; (backslash)
					sprintf(pOut, "&#%02d;", str[i]);
					pOut += 5;
				} else if (str[i]>=127) {
					//Device Control Characters
					sprintf(pOut, "&#%03d;", str[i]);
					pOut += 6;
				} else {
					*pOut = str[i];
					pOut++;
				}
				break;
		}
	}
	*pOut = '\0';
	strcpy(str, buffer);
}



/*
 * For web
 */
void web_debug_header(void)
{
		printf("Content-Type: text/plain;charset=utf-8\n\n");
}

