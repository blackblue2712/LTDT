// #include <stdio.h>

// void printRP (int n) {
// 	for(int i = 0; i < n; i++) {
// 		printf("*");
// 	}
// }

// int main () {
// 	int n;
// 	scanf("%d", &n);

// 	for(int i = 1; i <= n; i ++) {
// 		printRP(i);
// 		printf("\n");
// 	}

// 	return 0;
// }

// #include <stdio.h>

// void printRP (int n) {
// 	for(int i = 0; i < n; i++) {
// 		printf("*");
// 	}
// }

// void printSpace (int n) {
// 	for(int i = n; i > 0; i--) {
// 		printf(" ");
// 	}
// }

// int main () {
// 	int n;
// 	scanf("%d", &n);

// 	for(int i = 1; i <= n; i ++) {
// 		printSpace(n - i);
// 		printRP(i);
// 		printf("\n");
// 	}

// 	return 0;
// }

#include <stdio.h>

void printRP (int n) {
	for(int i = 0; i < n; i++) {
		printf("*");
	}
}

void printSpace (int n) {
	for(int i = n; i > 0; i--) {
		printf(" ");
	}
}

int main () {
	int n;
	scanf("%d", &n);

	for(int i = 1; i <= n; i ++) {
		printSpace(n - i);
		printRP(i*2 - 1);
		printf("\n");
	}

	return 0;
}

