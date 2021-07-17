#include <stdlib.h>

int main()
{
	char *tmp = (char *)malloc(100000000000);
	if (!tmp)
		printf("Error\n");
	printf("Success\n");
}