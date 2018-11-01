#include <stdio.h>
int main(int argc, char const *argv[])
{
	int x;
	int* p = &x;
	x = 10;
	*p = 20;
	printf("%d\n", x);
}