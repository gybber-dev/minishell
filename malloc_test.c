#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	char *tmp = (char *)malloc(100000000000);
	if (!tmp)
	{
		printf("Error: %d\n", errno);
		printf("Do it: %c\n", *tmp);
		exit(EXIT_FAILURE);
	}

	printf("Success\n");
}