#ifndef STRINGS_H
#define STRINGS_H

#include <stddef.h>

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

uint32_t strcmp(char *str1, char *str2)
{
	size_t len_s1 = strlen(str1);
	size_t len_s2 = strlen(str2);

	if(len_s1 != len_s2)
		return -1;

	uint32_t i = 0;

	while(str1[i] != '\0' && str2[i] != '\0' )
	{
		if(i + 1 > len_s1)
			return -1;

		if(str1[i] != str2[i])
			return -1;

		i++;
	}

	return 0;

} 

#endif