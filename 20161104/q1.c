#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

void main() {
	int x = 0x12345678;
	unsigned char *xp = (char *)&x;

	printf("&val = %d, xp= %d\n", &x, xp);

	printf("����Ʈ ����: %x %x %x %x\n", xp[0], xp[1], xp[2], xp[3]);

	printf("&val = %d, xp= %d\n", &x, &xp);

	printf("����Ʈ �ּ�: %d %d %d %d\n", &xp[0], &xp[1], &xp[2], &xp[3]);

	return 0;
}
