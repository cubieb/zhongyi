/*
 * For CGI 
 * 转换字符
 * char *src源字符串，char *last指向源串最后一个字符
 × char *dest转换后的字符串指针
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
			if(sscanf(src + 1， "%2x", &code) != 1)
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
