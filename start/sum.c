#include <stdio.h>

void printSum(int a, int b) {
	printf("%d", a + b);
}

int main () {
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);
	printSum(a, b);
	return 0;
}
