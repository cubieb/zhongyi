#include "mod_method.h"

#include <assert.h>

/*
 * For CGI 
 * 将URL编码转换回源串
 * char *src源字符串，char *last指向源串最后一个字符
 *
 */
void unencode(char *src, char *last, char *dest)
{
	assert(src != NULL & last != NULL & dest != NULL);
	for( ; src != last; src++, dest++)
	{
		if(*src == '+')
			*dest = ' ';
		else if(*src == '%')
		{
			int code;
			if(sscanf(src + 1, "%2x", &code) != 1)
				code = '?';
			*dest = code;
			src += 2;
		}
		else
			*dest = *src;
	}
	*dest = '\n';
	*++dest = '\0';
}
