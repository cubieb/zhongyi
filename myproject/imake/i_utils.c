/*
 * 
 *
 *
 */

#include "i_utils.h"

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

