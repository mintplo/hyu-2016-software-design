#include <stdio.h>
#include <math.h>

void merge(int *A, int *B, int *C, int size);

void main(void) {
	int A[4] = { 2,5,7,8 };
	int B[4] = { 1,3,4,6 };
	int C[8] = { 0, };

	merge(A, B, C, 4);

	for (int i = 0; i < 8; i++) {
		printf("%3d", C[i]);
	}
}

void merge(int *A, int *B, int *C, int size) {
	int a_index = 0;
	int b_index = 0;
	int c_index = 0;

	while (1) {
		// ��� �ϳ��� �迭�� ��Ұ� ������� Ŀ�������� ����
		if (a_index >= size || b_index >= size) {
			break;
		}

		// ��
		if (A[a_index] < B[b_index]) {
			C[c_index] = A[a_index];
			a_index++;
		}
		else {
			C[c_index] = B[b_index];
			b_index++;
		}

		c_index++;
	}

	// ���� ��� �迭�� �ֱ�
	for (int i = 0; i <= abs(a_index - b_index) - 1; i++) {
		if (a_index > b_index) {
			C[c_index + i] = B[b_index + i];
		}
		else {
			C[c_index + i] = A[a_index + i];
		}
	}
}