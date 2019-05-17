#include <stdio.h>
#define M 3
#define P 5
#define N 4

void main(void) {
	int i, j, k;
	float a[M][P] = { {1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3} };
	float b[P][N] = { {1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4} };
	float c[M][N] = { 0, }, *p;

	p = (float *)c;

	// 행렬 곱 계산
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < P; k++) {
				// 포인터 변수는 행렬이라는 정보를 가지고 있지 않아서
				// 행이 바뀌는 경우에는 그만큼의 사이즈를 넘어서 할당!
				*((p + (i*4)) + j) += *(*(a + i) + k) * *(*(b + k) + j);
			}
		}
	}

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			printf("%.3f\t", *((p + (i*4))+j));
		}

		printf("\n");
	}
}

