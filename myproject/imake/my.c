/*获取数据*/

#include "utils.h"

#include "mod_method.h"

#define INPUTSIZE 1024

#define MAXSIZE 2048


int main(int argc, char *argv[])
{
	int length;
	char *method;
	char *inputstr;

	method = getenv("REQUEST_METHOD");
	if(method == NULL)
		return -1;
	//POST方法
	if(!strcmp(method, "POST"))
	{
		length = atoi(getenv("CONTENT_LENGTH"));
		if(length != 0)
		{
			//必须申请缓存，应为stdin是不带缓存的
			inputstr = malloc(sizeof(char) * length + 1);
			if(inputstr == NULL)
				return -1;

			//从标准输入读取一定的数据
			fread(inputstr, sizeof(char), length, stdin);
		}
	}
	else if(!strcmp(method, "GET"))
	{
		inputstr = getenv("QUERY_STRING");
		length = strlen(inputstr);
	}
	if(length == 0)
		return -1;

	web_debug_header();
    
    char result[MAXSIZE];
    char dest[MAXSIZE];
	printf("%s\n", inputstr);
    get_nth_value(0, inputstr, '&', result, sizeof(result));
    printf("%s\n", result);
    get_nth_value(1, result, '=', result, sizeof(result));
    printf("%s\n", result);
    unencode(result, result+sizeof(result), dest);
    printf("%s\n", dest);
    
    get_nth_value(1, inputstr, '&', result, sizeof(result));
    printf("%s\n", result);
    get_nth_value(1, result, '=', result, sizeof(result));
    printf("%s\n", result);
    unencode(result, result+sizeof(result), dest);
    printf("%s\n", dest);
    
    get_nth_value(2, inputstr, '&', result, sizeof(result));
    printf("%s\n", result);
    get_nth_value(1, result, '=', result, sizeof(result));
	printf("%s\n", result);
    unencode(result, result+sizeof(result), dest);
    printf("%s\n", dest);
	return 0;
}
