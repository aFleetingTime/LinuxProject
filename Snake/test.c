#include <stdio.h>
#include <stdlib.h>

int main()
{
	system("stty raw");
	char ch = getchar();
	system("stty cooked");
	printf("%c\n", ch);
	return 0;
}
