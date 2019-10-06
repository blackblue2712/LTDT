// #include <stdio.h>

// int main () {
// 	int n;
// 	int buff[225];
// 	FILE* fp;
// 	fp = freopen("data.txt", "r", stdin);
// 	fscanf(fp, "%d", &n);

// 	for(int i = 0; i < n; i ++) {
// 		fscanf(fp, "%d", &buff[i]);
// 	}
	

// 	for(int i = 0; i < n; i ++) {
// 		for(int j = i + 1; j < n; j ++ ) {
// 			if(buff[j] < buff[i]) {
// 				int temp = buff[j];
// 				buff[j] = buff[i];
// 				buff[i] = temp;
// 			}
// 		}
// 	}

// 	for(int i = 0; i < n; i++) {
// 		printf("%d ", buff[i]);
// 	}

// 	return 0;
// }



#include <stdio.h>

int main () {
	int n;
	int buff[225];
	scanf("%d", &n);

	for(int i = 0; i < n; i ++) {
		scanf("%d", &buff[i]);
	}
	

	for(int i = 0; i < n; i ++) {
		for(int j = i + 1; j < n; j ++ ) {
			if(buff[j] < buff[i]) {
				int temp = buff[j];
				buff[j] = buff[i];
				buff[i] = temp;
			}
		}
	}

	for(int i = 0; i < n; i++) {
		printf("%d ", buff[i]);
	}

	return 0;
}

