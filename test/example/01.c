/*获取数据*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_input(void)
{
	int length;
	char *method;
	char *inputstring;

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
			inputstring = malloc(sizeof(char) * length + 1);
			if(inputstring == NULL)
				return -1;

			//从标准输入读取一定的数据
			fread(inputstring, sizeof(char), length, stdin);
		}
	}
	else if(!strcmp(method, "GET"))
	{
		inputstring = getenv("QUERY_STRING");
		length = strlen(inputstring);
	}
	if(length == 0)
		return 0;

}
